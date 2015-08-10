/*
 * ODE45.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: alex
 */

#include <fstream>
#include <assert.h>

#include "ODE45.h"

#include "../common.h"
#include "../debugLog/debugLog.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////        Initialize functions for solver
////////////
void baseODE45::solve_init(std::vector<double> const &init_initial_conditions)
{
    res.clear();
    res.push_back(init_initial_conditions);
}

void baseODE45::solve_init(double const &init_step_length, unsigned const &init_amount_steps)
{
    step_length         = init_step_length;
    amount_steps        = init_amount_steps;
}

void baseODE45::solve_init(std::vector<double> const &init_initial_conditions, double const &init_step_length)
{
    step_length         = init_step_length;
    res.clear();
    res.push_back(init_initial_conditions);
}

void baseODE45::solve_init(std::vector<double> const &init_initial_conditions, double const &init_step_length, unsigned const &init_amount_steps)
{
    step_length         = init_step_length;
    amount_steps        = init_amount_steps;
    res.clear();
    res.push_back(init_initial_conditions);
}

void baseODE45::solve_init_step_length(double const &init_step_length)
{
    step_length = init_step_length;
}
////////////
////////////        END Initialize functions for solver
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////        Different solver's run functions for solver
////////////
void baseODE45::solve(unsigned init_amount_steps)
{
    amount_steps = init_amount_steps;

    solve();
}

void baseODE45::solve(std::vector<double> init_initial_conditions)
{
    res.clear();
    res.push_back(init_initial_conditions);

    solve();
}
void baseODE45::solve(double init_step_length, unsigned init_amount_steps)
{
    step_length         = init_step_length;
    amount_steps        = init_amount_steps;

    solve();
}

void baseODE45::solve(std::vector<double> init_initial_conditions, double init_step_length, unsigned init_amount_steps)
{
    step_length         = init_step_length;
    amount_steps        = init_amount_steps;
    res.clear();
    res.push_back(init_initial_conditions);

//    tmp_log_ostringstream.clear();
//    tmp_log_ostringstream << "Start solve for ODE45 with configure ALL parameters step_length:" << step_length << " steps:" << amount_steps;
    LM(LI,  "Start solve for ODE45 with configure ALL parameters step_length:" << step_length << " steps:" << amount_steps);
    //LM(LI, "Start solve for ODE45 with configure ALL parameters step_length:" + std::to_string(step_length) + " steps:" + std::to_string(amount_steps));

    solve();
}

void baseODE45::solve()
{
    if (res.size() == 0)
    {
        LM(LE, "Need to set initial conditions for ODE");
        assert(false);
    }
    std::vector<double> X, C, K1, K2, K3, K4;

    X = res.back();

    for (unsigned step = 0; step < amount_steps; ++step)
    {

        solve_one_step(X, C, K1, K2, K3, K4);
    }
}
////////////
////////////        END Different solver's run functions for solver
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////        Helper functions for solver
////////////
inline void baseODE45::solve_one_step(    std::vector<double> &X
                                    , std::vector<double> &C
                                    , std::vector<double> &K1
                                    , std::vector<double> &K2
                                    , std::vector<double> &K3
                                    , std::vector<double> &K4   )
{
    K1 = calcFunc(X);
    K2 = calcFunc(calc_K_by_h_div_2(X,K1,step_length));
    K3 = calcFunc(calc_K_by_h_div_2(X,K2,step_length));
    K4 = calcFunc(calc_K_by_h(X,K1,step_length));

    X = calc_new_X(X, K1, K2, K3, K4, step_length);
    res.push_back(X);
}


std::vector<double> baseODE45::calc_K_by_h(std::vector<double> const &X, std::vector<double> const &K, double const &h)
{
    std::vector<double> res(X.size());

    for (unsigned i = 0; i < X.size(); ++i)
    {
        res[i] = X[i] + K[i] * h;
    }

    return res;
}


std::vector<double> baseODE45::calc_new_X(std::vector<double> const &X
        , std::vector<double> const &K1
        , std::vector<double> const &K2
        , std::vector<double> const &K3
        , std::vector<double> const &K4
        , double step_length)
{
    std::vector<double> res(X.size());

    res[0] = X[0] + step_length;

    for (unsigned i = 1; i < X.size(); ++i)
    {
        res[i] = X[i] + step_length * (K1[i] + 2.0*K2[i] + 2.0*K3[i] + K4[i]) / 6.0;
    }

//    LM(LD, "nex T: " << res[0] << " X:" << res[1])
    return res;
}
////////////
////////////        END Helper functions for solver
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




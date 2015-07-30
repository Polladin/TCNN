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
////////////        Solver with different parameters
////////////
void ODE45::solve(std::vector<double> init_initial_conditions, double init_step_length, unsigned init_amount_steps)
{
    step_length         = init_step_length;
    amount_steps        = init_amount_steps;
    res.clear();
    res.push_back(init_initial_conditions);

    solve();
}

void ODE45::solve(double init_step_length, unsigned init_amount_steps)
{
    step_length     = init_step_length;
    amount_steps    = init_amount_steps;

    solve();
}

void ODE45::solve(std::vector<double> init_initial_conditions)
{
    res.clear();
    res.push_back(init_initial_conditions);

    LM(LI, "Start solve for ODE45 with params: step_length-" + std::to_string(step_length) + " steps-" + std::to_string(amount_steps));

    solve();
}

void ODE45::solve(unsigned init_amount_steps)
{
    amount_steps = init_amount_steps;

    solve();
}

void ODE45::solve()
{
   std::vector<double> X, C, K1, K2, K3, K4;

   X = res.back();

   for (unsigned step = 0; step < amount_steps; ++step)
   {
       solve_one_step(X, C, K1, K2, K3, K4);
   }
}


inline void ODE45::solve_one_step(    std::vector<double> &X
                                    , std::vector<double> &C
                                    , std::vector<double> &K1
                                    , std::vector<double> &K2
                                    , std::vector<double> &K3
                                    , std::vector<double> &K4   )
{
   K1 = calc_func(X);
   K2 = calc_func(calc_K_by_h_div_2(X,K1,step_length));
   K3 = calc_func(calc_K_by_h_div_2(X,K2,step_length));
   K4 = calc_func(calc_K_by_h(X,K1,step_length));

   X = calc_new_X(X, K1, K2, K3, K4, step_length);
   res.push_back(X);
}
////////////
////////////        END Solver with different parameters
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////        Helper functions for solver
////////////
std::vector<double> ODE45::calc_K_by_h(std::vector<double> const &X, std::vector<double> const &K, double const &h)
{
    std::vector<double> res(X.size());

    for (unsigned i = 0; i < X.size(); ++i)
    {
        res[i] = X[i] + K[i] * h;
    }

    return res;
}

std::vector<double> ODE45::calc_new_X(std::vector<double> const &X
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
    return res;
}
////////////
////////////        END Helper functions for solver
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






/*
 * ODE45.h
 *
 *  Created on: Jul 19, 2015
 *      Author: alex
 */

#ifndef SRC_ODE45_ODE45_H_
#define SRC_ODE45_ODE45_H_

#include <vector>
#include <fstream>

#include "../debugLog/debugLog.h"
#include "../common.h"



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////        BASE ODE class
class baseODE45
{
public:
    baseODE45(){}
    virtual ~baseODE45() {}

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Pure virtual function to specify solving function
    virtual std::vector<double> calcFunc(std::vector<double> const &X) = 0;
    ////////////        END Pure virtual function to specify solving function
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Functions to get a result
    std::vector<std::vector<double> > result_take() { return res; }

    std::vector<std::vector<double> >::iterator result_iterator_begin() { return res.begin(); }
    std::vector<std::vector<double> >::iterator result_iterator_end() { return res.end(); }

    bool result_write_to_file(const char *file_name) { return write_to_file(file_name, res); }
    ////////////        END Functions to get a result
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Initialize functions for solver
    void solve_init(std::vector<double> const &init_initial_conditions);
    void solve_init(double const &init_step_length, unsigned const &init_amount_steps);
    void solve_init(std::vector<double> const &init_initial_conditions, double const &init_step_length);
    void solve_init(std::vector<double> const &init_initial_conditions, double const &init_step_length, unsigned const &init_amount_steps);

    void solve_init_step_length(double const &init_step_length);
    ////////////        END Initialize functions for solver
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Different solver's run functions for solver
    void solve();
    void solve(unsigned init_amount_steps);
    void solve(std::vector<double> init_initial_conditions);
    void solve(double init_step_length, unsigned init_amount_steps);
    void solve(std::vector<double> init_initial_conditions, double init_step_length, unsigned init_amount_steps);
    ////////////        END Different solver's run functions for solver
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<double> solve_get_next()
    {
        solve(1);
        return res.back();
    }


protected:
    double      step_length     {0.1};
    unsigned    amount_steps    {10};

    std::vector<std::vector<double> > res;

private:

    std::vector<double> calc_K_by_h(std::vector<double> const &X, std::vector<double> const &K, double const &h);

    std::vector<double> calc_K_by_h_div_2(std::vector<double> const &X, std::vector<double> const &K, double const &h)
    {
        return calc_K_by_h(X, K, h/2.0);
    }

    std::vector<double> calc_new_X(   std::vector<double> const &X
                                    , std::vector<double> const &K1
                                    , std::vector<double> const &K2
                                    , std::vector<double> const &K3
                                    , std::vector<double> const &K4
                                    , double step_length                );

    inline void solve_one_step(   std::vector<double> &X
                                , std::vector<double> &C
                                , std::vector<double> &K1
                                , std::vector<double> &K2
                                , std::vector<double> &K3
                                , std::vector<double> &K4       );

};
////////////        END BASE ODE class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




#endif /* SRC_ODE45_ODE45_H_ */

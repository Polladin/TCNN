/*
 * ODE45.h
 *
 *  Created on: Jul 19, 2015
 *      Author: alex
 */

#ifndef SRC_ODE45_ODE45_H_
#define SRC_ODE45_ODE45_H_

#include <vector>
#include "../common.h"

class ODE45
{
public:

    ODE45() {}
    virtual ~ODE45() {}


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Functions to get a result
    bool result_write_to_file(const char* file_name) { return write_to_file(file_name, res); }

    std::vector<std::vector<double> > result_take() { return res; }

    std::vector<std::vector<double> >::iterator result_iterator_begin() { return res.begin(); }
    std::vector<std::vector<double> >::iterator result_iterator_end() { return res.end(); }

    std::vector<double> result_last() { return res.back(); }
    ////////////        END Functions to get a result
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void solve();
    void solve(unsigned init_amount_steps);
    void solve(std::vector<double> init_initial_conditions);
    void solve(double init_step_length, unsigned init_amount_steps);
    void solve(std::vector<double> init_initial_conditions, double init_step_length, unsigned init_amount_steps);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Functions to set up initial conditions
    void set_initial_conditions(std::vector<double> init_initial_conditions) { res.clear(); res.push_back(init_initial_conditions); }
    void set_step_length(double init_step_length) { step_length = init_step_length; }
    void set_amount_steps(unsigned init_amount_steps) { amount_steps = init_amount_steps; }
    ////////////        END Functions to set up initial conditions
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Pure virtual function to specify solving function
    virtual std::vector<double> calc_func(std::vector<double> X) = 0;
    ////////////        END Pure virtual function to specify solving function
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


protected:

    std::vector<std::vector<double> > res;

    double      step_length     {0.1};
    unsigned    amount_steps    {10};

    std::vector<double> initial_conditions;


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


#endif /* SRC_ODE45_ODE45_H_ */

/*
 * ODE45.h
 *
 *  Created on: Jul 19, 2015
 *      Author: alex
 */

#ifndef SRC_ODE45_ODE45_H_
#define SRC_ODE45_ODE45_H_

#include <vector>


class ODE45
{
public:

    ODE45() {}
    virtual ~ODE45() {}

    std::vector<std::vector<double> > run_ode(std::vector<double> initial_conditions, double step_length, unsigned amount_steps );

    bool result_write_to_file(const char* file_name) { return write_to_file(file_name, res); }

    std::vector<std::vector<double> > result_take() { return res; }

    std::vector<double> get_next();

    void solve();
    void solve(unsigned init_amount_steps)
    void solve(std::vector<double> init_initial_conditions);
    void solve(double init_step_length, unsigned init_amount_steps);
    void solve(std::vector<double> init_initial_conditions, double init_step_length, unsigned init_amount_steps);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Functions to set up initial conditions
    void set_initial_conditions(std::vector<double> init_initial_conditions) { initial_conditions = init_initial_conditions; }
    void set_step_length(double init_step_length) { step_length = init_step_length; }
    void set_amount_steps(unsigned init_amount_steps) { amount_steps = init_amount_steps; }
    ////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Pure virtual function to specify solving function
    virtual std::vector<double> calc_func(std::vector<double> X) = 0;
    ////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    inline void ODE45::solve_one_step(    std::vector<double> &X
                                        , std::vector<double> &C
                                        , std::vector<double> &K1
                                        , std::vector<double> &K2
                                        , std::vector<double> &K3
                                        , std::vector<double> &K4       );





    std::vector<std::vector<double> > res;

    double      step_length     {0.1};
    unsigned    amount_steps    {10};

    std::vector<double> initial_conditions;
};


#endif /* SRC_ODE45_ODE45_H_ */

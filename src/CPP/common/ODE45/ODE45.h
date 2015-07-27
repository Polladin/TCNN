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

    virtual std::vector<double> calc_func(std::vector<double> X) = 0;

    std::vector<std::vector<double> > get_resul() { return res; }

    bool write_result_in_file(const char* file_name);

private:

    std::vector<std::vector<double> > solve(std::vector<double> X, double step_length, unsigned amount_steps);

    std::vector<double> calc_K_by_h(std::vector<double> const &X, std::vector<double> const &K, double const &h);

    std::vector<double> calc_K_by_h_div_2(std::vector<double> const &X, std::vector<double> const &K, double const &h)
    {
        return calc_K_by_h(X, K, h/2.0);
    }

    std::vector<double> calc_new_X(std::vector<double> const &X
            , std::vector<double> const &K1
            , std::vector<double> const &K2
            , std::vector<double> const &K3
            , std::vector<double> const &K4
            , double step_length                );



    std::vector<std::vector<double> > res;
};


#endif /* SRC_ODE45_ODE45_H_ */

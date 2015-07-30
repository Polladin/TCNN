/*
 * TCNN_opt_function.h
 *
 *  Created on: Jul 27, 2015
 *      Author: alex
 */

#ifndef CPP_TCNN_OPT_FUNCTION_FUNCTIONS_TCNN_OPT_FUNCTION_H_
#define CPP_TCNN_OPT_FUNCTION_FUNCTIONS_TCNN_OPT_FUNCTION_H_

#include "../chaotic/chaotic.h"

#define PI 3.14159265359

class TCNN_opt_function : public ODE45
{
public:
    TCNN_opt_function();

    ~TCNN_opt_function(){};

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Virtual function to specify solving function
    virtual std::vector<double> calc_func(std::vector<double> X);
    ////////////        END Virtual function to specify solving function
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void solve_function(std::vector<double> init_initial_conditions, double init_step_length, unsigned init_amount_steps)
    {
        solve(init_initial_conditions, init_step_length, init_amount_steps);
    }

    std::vector<std::vector<double> > result_function_take() { return result_take(); }

    double df_gen(double x, double h);

    double func(double x);

    bool write_func_to_file(double x_begin, double x_end, unsigned steps, const char* file_name);

    bool write_chaos_to_file(const char* file_name);

private:
    Chaotic chaos_fuction;

    double chaotic_coeff            {10};
    double chaotic_reduce_coeff     {0.999};
    double alpha                    {0.5};
};


#endif /* CPP_TCNN_OPT_FUNCTION_FUNCTIONS_TCNN_OPT_FUNCTION_H_ */

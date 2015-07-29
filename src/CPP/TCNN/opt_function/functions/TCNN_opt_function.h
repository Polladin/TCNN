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
    TCNN_opt_function(double step_length);

    virtual std::vector<double> calc_func(std::vector<double> X);

    double df_gen(double x, double h);

    double func(double x);

    bool write_func_to_file(double x_begin, double x_end, unsigned steps, const char* file_name);

    bool write_chaos_to_file(const char* file_name);



    Chaotic chaos_fuction;
private:

    double chaotic_coeff;

    double chaotic_reduce_coeff;

    double step_length;

    double alpha;
};


#endif /* CPP_TCNN_OPT_FUNCTION_FUNCTIONS_TCNN_OPT_FUNCTION_H_ */

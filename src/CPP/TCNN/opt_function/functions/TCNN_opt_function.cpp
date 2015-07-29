/*
 * TCNN_opt_function.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: alex
 */

#include <fstream>
#include <cmath>

#include "TCNN_opt_function.h"
#include "../../../common/debugLog/debugLog.h"


TCNN_opt_function::TCNN_opt_function(double step_length_init)
{
    alpha = 0.5;
    step_length = step_length_init;

    chaotic_coeff = 10;
    chaotic_reduce_coeff = 1 - step_length / 100.0;

    std::vector<double> X;
    X.push_back(0);
    X.push_back(-0.1);
    X.push_back(0);
    X.push_back(0);
    chaos_fuction.run_ode(X, step_length,1);
}

double TCNN_opt_function::df_gen(double x, double h)
{
    return (  -137.0 * func(x) + 300.0 * func(x + h) - 300.0 * func(x + 2.0*h)
              + 200.0 * func(x + 3.0*h) - 75.0 * func(x + 4.0*h) + 12.0 * func(x + 5.0*h)
           ) / (60 * h);
}

double TCNN_opt_function::func(double x)
{

//    return (x-0.5)*(x-0.5);
    return ((x-0.9)-0.2)*((x-0.9)-0.2) + std::cos(3.0*PI*(x-0.9));
//    return -20.0*std::exp(-0.2*std::sqrt(0.5*(x[0]*x[0]+x[1]*x[1]))) - std::exp(0.5*(std::cos(2.0*PI*x[0])+std::cos(2.0*PI*x[1]))) + std::exp(1) + 20;
}

std::vector<double> TCNN_opt_function::calc_func(std::vector<double> X)
{
    std::vector<double> dX(X.size());
    std::vector<double> chaoticValue = chaos_fuction.get_next();

    dX[0] = 1;
    dX[1] = chaotic_coeff*chaoticValue[3] - alpha * df_gen(X[1], 0.00001); //chaoticValue[2]

    chaotic_coeff *= chaotic_reduce_coeff;

    return dX;
}


bool TCNN_opt_function::write_func_to_file(double x_begin, double x_end, unsigned steps, const char* file_name)
{
    if (x_end < x_begin)
    {
        LM(LW, "x_begin should be less than x_end");
        return false;
    }

    std::vector<std::vector<double> > function_values;

    double delta = (x_end - x_begin) / steps;

    for (double x = x_begin; x < x_end; x += delta)
    {
        std::vector<double> row;
        row.push_back(x);
        row.push_back(func(x));

        function_values.push_back(row);
    }


    //TODO : make common function to write in file
    try
    {
        std::ofstream file_out;
        file_out.open (file_name, std::ios::out );

        for(auto const &row : function_values)
        {
            for (auto const &elem : row)
            {
                file_out << elem << "\t";
            }
            file_out << "\n";
        }
    }
    catch(...)
    {
        return false;
    }

    return true;
}


bool TCNN_opt_function::write_chaos_to_file(const char* file_name)
{
    return chaos_fuction.write_result_in_file(file_name);
}


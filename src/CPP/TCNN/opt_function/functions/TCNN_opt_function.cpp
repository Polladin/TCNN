/*
 * TCNN_opt_function.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: alex
 */

#include <cmath>

#include "TCNN_opt_function.h"


TCNN_opt_function::TCNN_opt_function()
{
    alpha = 0.5;
    step_length = 0.1;

    std::vector<double> X;
    X.push_back(0);
    X.push_back(-0.1);
    X.push_back(0);
    X.push_back(0);
    chaos_fuction.solve(X, step_length,1);
}

double TCNN_opt_function::df_gen(double x, double h)
{
    return (  -137.0 * func(x) + 300.0 * func(x + h) - 300.0 * func(x + 2.0*h)
              + 200.0 * func(x + 3.0*h) - 75.0 * func(x + 4.0*h) + 12.0 * func(x + 5.0*h)
           ) / (60 * h);
}

double TCNN_opt_function::func(double x)
{
    return ((x-0.9)-0.2)*((x-0.9)-0.2) + std::cos(3.0*PI*(x-0.9));
    //return -20.0*std::exp(-0.2*std::sqrt(0.5*(x[0]*x[0]+x[1]*x[1]))) - std::exp(0.5*(std::cos(2.0*PI*x[0])+std::cos(2.0*PI*x[1]))) + std::exp(1) + 20;
}

std::vector<double> TCNN_opt_function::calc_func(std::vector<double> X)
{
    std::vector<double> dX(X.size());
    std::vector<double> chaoticValue = chaos_fuction.get_next();

    dX[0] = 1;
    dX[1] = chaoticValue[2] - alpha * df_gen(X[1], step_length);

    return dX;
}

/*
 * ODE45.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: alex
 */

#include <fstream>

#include "ODE45.h"
#include "../debugLog.h"

std::vector<std::vector<double> > ODE45::run_ode(std::vector<double> initial_conditions, double step_length, unsigned amount_steps )
{
    LM(LD,"run_ode");
    return solve(initial_conditions, step_length, amount_steps);
}


std::vector<std::vector<double> > ODE45::solve(std::vector<double> X, double step_length, unsigned amount_steps)
{
   std::vector<double> C, K1, K2, K3, K4;

   res.clear();
   res.push_back(X);

   for (unsigned step = 0; step < amount_steps; ++step)
   {
       K1 = calc_func(X);
       K2 = calc_func(calc_K_by_h_div_2(X,K1,step_length));
       K3 = calc_func(calc_K_by_h_div_2(X,K2,step_length));
       K4 = calc_func(calc_K_by_h(X,K1,step_length));

       X = calc_new_X(X, K1, K2, K3, K4, step_length);
       res.push_back(X);
   }

   return res;
}


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


bool ODE45::write_result_in_file(const char* file_name)
{
    try
    {
        std::ofstream file_out;
        file_out.open (file_name, std::ofstream::out );

        for(auto const &row : res)
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





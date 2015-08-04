/*
 * TCNN_opt_function.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: alex
 */

#include <fstream>
#include <cmath>

#include "TCNN_opt_function.h"
#include "../../common/debugLog/debugLog.h"
#include "../../common/common.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////        Initialize function
////////////
void TCNN_opt_function::init_optimizer_initial_conditions (std::vector<double> const &init_initial_conditions)
{
    res.clear();
    res.push_back(init_initial_conditions);
}

void TCNN_opt_function::init_optimizer_step_length (double const &init_step_length)
{
    step_length = init_step_length;
    recalc_chaotic_reduce_coeff();
}

void TCNN_opt_function::init_optimizer_amount_steps (double const &init_amount_steps)
{
    amount_steps = init_amount_steps;
}

void TCNN_opt_function::init_optimizer_chaotic_coeff (double const &init_chaotic_coeff)
{
    chaotic_coeff = init_chaotic_coeff;
}

void TCNN_opt_function::init_optimizer_chaotic_reduce_coeff (double const &init_chaotic_reduce_coeff)
{
    chaotic_reduce_coeff = init_chaotic_reduce_coeff;
}

void TCNN_opt_function::init_optimizer_alpha (double const &init_alpha)
{
    alpha = init_alpha;
}

void TCNN_opt_function::init_optimizer_step_length_wo_recalc_chaotic_reduce_coeff (double const &init_step_length)
{
    step_length = init_step_length;
}



void TCNN_opt_function::init_optimizer(   std::vector<double> const &init_initial_conditions
                                        , double const &init_step_length
                                        , unsigned const &init_amount_steps
                                        , double const &init_chaotic_coeff
                                        , double const &init_chaotic_reduce_coeff
                                        , double const &init_alpha                             )
{
    init_optimizer_initial_conditions(init_initial_conditions);
    init_optimizer_step_length_wo_recalc_chaotic_reduce_coeff(init_step_length);
    init_optimizer_amount_steps(init_amount_steps);
    init_optimizer_chaotic_coeff(init_chaotic_coeff);
    init_optimizer_chaotic_reduce_coeff(init_chaotic_reduce_coeff);
    init_optimizer_alpha(init_alpha);
}

void TCNN_opt_function::init_optimizer(   std::vector<double> const &init_initial_conditions
                                        , double const &init_step_length
                                        , unsigned const &init_amount_steps
                                        , double const &init_chaotic_coeff
                                        , double const &init_alpha                             )
{
    init_optimizer_initial_conditions(init_initial_conditions);
    init_optimizer_step_length(init_step_length);
    init_optimizer_amount_steps(init_amount_steps);
    init_optimizer_chaotic_coeff(init_chaotic_coeff);
    init_optimizer_alpha(init_alpha);
}

void TCNN_opt_function::init_optimizer(   std::vector<double> const &init_initial_conditions
                                        , double const &init_step_length
                                        , unsigned const &init_amount_steps                    )
{
    init_optimizer_initial_conditions(init_initial_conditions);
    init_optimizer_step_length(init_step_length);
    init_optimizer_amount_steps(init_amount_steps);
}

void TCNN_opt_function::init_optimizer(   double const &init_chaotic_coeff
                                        , double const &init_chaotic_reduce_coeff
                                        , double const &init_alpha                             )
{
    init_optimizer_chaotic_coeff(init_chaotic_coeff);
    init_optimizer_chaotic_reduce_coeff(init_chaotic_reduce_coeff);
    init_optimizer_alpha(init_alpha);
}

void TCNN_opt_function::init_optimizer(   double const &init_chaotic_coeff
                                        , double const &init_chaotic_reduce_coeff              )
{
    init_optimizer_chaotic_coeff(init_chaotic_coeff);
    init_optimizer_chaotic_reduce_coeff(init_chaotic_reduce_coeff);
}

void TCNN_opt_function::init_chaotic(std::vector<double> const &init_initial_conditions, double const &init_step_length)
{
    chaos_fuction->solve_init(init_initial_conditions, init_step_length);
}
void TCNN_opt_function::init_chaotic(double const &init_step_length)
{
    chaos_fuction->solve_init_step_length(init_step_length);
}
////////////
////////////        END Initialize function
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





TCNN_opt_function::TCNN_opt_function()
{
    std::vector<double> X;
    X.push_back(0);
    X.push_back(-0.1);
    X.push_back(0);
    X.push_back(0);

    init_optimizer_initial_conditions(X);

    chaos_fuction = new Chaotic1;
    chaos_fuction->solve_init(X, step_length);

    optimized_function = new OptimizedFunc_1;
}

TCNN_opt_function::TCNN_opt_function(baseODE45 *init_chaotic_function, OptimizedFunc *init_optimized_function)
{
    std::vector<double> X;
    X.push_back(0);
    X.push_back(-0.1);
    X.push_back(0);
    X.push_back(0);

    init_optimizer_initial_conditions(X);

    chaos_fuction = init_chaotic_function;
    chaos_fuction->solve_init(X, step_length);

    optimized_function = init_optimized_function;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////        Run optimization with different parameters
////////////
void TCNN_opt_function::run_optimization()
{
    baseODE45::solve();
}

void TCNN_opt_function::run_optimization(unsigned const &init_amount_steps)
{
    amount_steps = init_amount_steps;
    baseODE45::solve();
}

void TCNN_opt_function::run_optimization(std::vector<double> const &init_initial_conditions)
{
    baseODE45::solve(init_initial_conditions, step_length, amount_steps);
}

void TCNN_opt_function::run_optimization(double const &init_step_length, unsigned const &init_amount_steps)
{
    step_length = init_step_length;
    amount_steps = init_amount_steps;
    baseODE45::solve();
}

void TCNN_opt_function::run_optimization(std::vector<double> const &init_initial_conditions, double const &init_step_length, unsigned const &init_amount_steps)
{
    baseODE45::solve(init_initial_conditions, init_step_length, init_amount_steps);
}
////////////
////////////        END Run optimization with different parameters
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//double TCNN_opt_function::df_gen(double x, double h)
//{
//    return (  -137.0 * func(x) + 300.0 * func(x + h) - 300.0 * func(x + 2.0*h)
//              + 200.0 * func(x + 3.0*h) - 75.0 * func(x + 4.0*h) + 12.0 * func(x + 5.0*h)
//           ) / (60 * h);
//}
//
//double TCNN_opt_function::func(double x)
//{
//
////    return (x-0.5)*(x-0.5);
//    return ((x-0.9)-0.2)*((x-0.9)-0.2) + std::cos(3.0*PI*(x-0.9));
////    return -20.0*std::exp(-0.2*std::sqrt(0.5*(x[0]*x[0]+x[1]*x[1]))) - std::exp(0.5*(std::cos(2.0*PI*x[0])+std::cos(2.0*PI*x[1]))) + std::exp(1) + 20;
//}

std::vector<double> TCNN_opt_function::calcFunc(std::vector<double> const &X)
{
    std::vector<double> dX(X.size());
    std::vector<double> chaoticValue = chaos_fuction->solve_get_next();

    dX[0] = 1;
    dX[1] = chaotic_coeff*chaoticValue[3] - alpha * optimized_function->dF(X,1,0.00001); //  df_gen(X[1], 0.00001); //chaoticValue[2]

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
        std::vector<double> tmp_data;
        tmp_data.push_back(x);
        tmp_data.push_back(x);
        row.push_back(optimized_function->fVal(tmp_data));

        function_values.push_back(row);
    }

    write_to_file(file_name, function_values);

    return true;
}


bool TCNN_opt_function::write_chaos_to_file(const char* file_name)
{
    return write_to_file(file_name, chaos_fuction->result_take());
}


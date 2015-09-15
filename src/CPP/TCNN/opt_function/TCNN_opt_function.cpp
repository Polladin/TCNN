/*
 * TCNN_opt_function.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: alex
 */

#include <fstream>
#include <cmath>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void TCNN_opt_function::init_optimizer_set_amount_chaotic_func (unsigned const& amount_chaotic_functions, double chaotic_step_length)
{
    double rand_initial_cond;
    srand (time(0));

    for(auto *elem : chaos_fuctions)
    {
        delete elem;
    }
    chaos_fuctions.clear();

    for (int i=0; i<100; ++i)
    {
        rand_initial_cond = 2.0 * (static_cast<double>(rand())/RAND_MAX-0.5) * 0.2;
    }

    for (unsigned i = 0; i < amount_chaotic_functions; ++i)
    {
        rand_initial_cond = 2.0 * (static_cast<double>(rand())/RAND_MAX-0.5) * 0.2;

        LM(LI, "rand initial cond: " << rand_initial_cond)

        std::vector<double> X;
        X.push_back(0);
        X.push_back(rand_initial_cond);
        X.push_back(0);
        X.push_back(0);

        chaos_fuctions.push_back(new Chaotic1);
        chaos_fuctions.back()->solve_init(X, chaotic_step_length);
    }
}

void TCNN_opt_function::init_optimizer_fuction(OptimizedFunc *init_optimized_function)
{
    delete optimized_function;

    optimized_function = init_optimized_function;
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






void TCNN_opt_function::init_chaotic(std::vector<std::vector<double> > const &init_initial_conditions, double const &init_step_length)
{
    if (!isInitialConditionsHasSameDimentions(init_initial_conditions)) return;

    std::vector<std::vector<double> >::const_iterator it_initial_conditions = init_initial_conditions.begin();
    for (auto *p_chaos : chaos_fuctions)
    {
        p_chaos->solve_init(*it_initial_conditions, init_step_length);
        ++it_initial_conditions;
    }
}

void TCNN_opt_function::init_chaotic(double const &init_step_length)
{
    init_chaotic(initial_conditions, init_step_length);
}


bool TCNN_opt_function::isInitialConditionsHasSameDimentions(std::vector<std::vector<double> > const &init_initial_conditions)
{
    if (init_initial_conditions.size() != chaos_fuctions.size())
    {
        LM(LE, "Size of vector with initial conditions are not equal to size of vector chaotic functions");
        return false;
    }

    return true;
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

    chaos_fuctions.push_back(new Chaotic1);
    for (baseODE45 *p_chaos : chaos_fuctions) p_chaos->solve_init(X, step_length);

    optimized_function = new OptimizedFunc_1;
}

TCNN_opt_function::TCNN_opt_function(unsigned const &amount_chaotic_functions, double chaotic_step_length)
{
    init_optimizer_set_amount_chaotic_func(amount_chaotic_functions, chaotic_step_length);

    optimized_function = new OptimizedFunc_1;
}

TCNN_opt_function::TCNN_opt_function(baseODE45 *init_chaotic_function, OptimizedFunc *init_optimized_function)
{
    std::vector<double> X;
    X.push_back(0);
    X.push_back(-0.1);
    X.push_back(0);
    X.push_back(0);

//    init_optimizer_initial_conditions(X);

    chaos_fuctions.push_back(init_chaotic_function);
    for (baseODE45 *p_chaos : chaos_fuctions) p_chaos->solve_init(X, step_length);

//    chaos_fuction = init_chaotic_function;
//    chaos_fuction->solve_init(X, step_length);

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
    std::vector<double> chaoticValue;

    for (auto *p_chaos : chaos_fuctions)
    {
        std::vector<double> tmp = p_chaos->solve_get_next();
        chaoticValue.push_back(tmp[3]);
    }

    double exp_chaotic_coeff = chaotic_coeff / std::exp(X[0] * chaotic_reduce_coeff);

    dX[0] = 1;
    for (unsigned i = 1; i < X.size(); ++i)
    {
        dX[i] = exp_chaotic_coeff*chaoticValue[i-1] - alpha * optimized_function->dF(X,i,0.00001);
    }

//    chaotic_coeff *= chaotic_reduce_coeff;

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
    char buff[255];
    unsigned idx = 0;
    for (auto *p_chaos : chaos_fuctions)
    {
        sprintf(buff, "%s_%u",file_name, idx++);
        write_to_file(buff, p_chaos->result_take());
    }
    return true;
}


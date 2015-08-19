/*
 * TCNN_opt_function.h
 *
 *  Created on: Jul 27, 2015
 *      Author: alex
 */

#ifndef CPP_TCNN_OPT_FUNCTION_FUNCTIONS_TCNN_OPT_FUNCTION_H_
#define CPP_TCNN_OPT_FUNCTION_FUNCTIONS_TCNN_OPT_FUNCTION_H_

#include <vector>

#include "../chaotic/chaotic.h"
#include "../../common/ODE45/ODE45.h"
#include "functions/func_to_optimize.h"

class TCNN_opt_function : public baseODE45
{
public:
    TCNN_opt_function();
    TCNN_opt_function(unsigned const &amount_chaotic_functions);
    TCNN_opt_function(baseODE45 *init_chaotic_function, OptimizedFunc *optimized_function);
    ~TCNN_opt_function()
    {
        for(auto *p_chaos : chaos_fuctions)
        {
            delete p_chaos;
        }

        delete optimized_function;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Virtual function to specify solving function
    virtual std::vector<double> calcFunc(std::vector<double> const &X);
    ////////////        END Virtual function to specify solving function
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Initialize function
    void init_optimizer_fuction(OptimizedFunc *init_optimized_function);

    void init_optimizer(  std::vector<double> const &init_initial_conditions
                        , double const &init_step_length
                        , unsigned const &init_amount_steps
                        , double const &init_chaotic_coeff
                        , double const &init_chaotic_reduce_coeff
                        , double const &init_alpha                             );

    void init_optimizer(  std::vector<double> const &init_initial_conditions
                        , double const &init_step_length
                        , unsigned const &init_amount_steps
                        , double const &init_chaotic_coeff
                        , double const &init_alpha                             );

    void init_optimizer(  std::vector<double> const &init_initial_conditions
                        , double const &init_step_length
                        , unsigned const &init_amount_steps                    );

    void init_optimizer(  double const &init_chaotic_coeff
                        , double const &init_chaotic_reduce_coeff
                        , double const &init_alpha                             );

    void init_optimizer(  double const &init_chaotic_coeff
                        , double const &init_chaotic_reduce_coeff              );

    void init_optimizer_initial_conditions      (std::vector<double> const &init_initial_conditions);
    void init_optimizer_step_length             (double const &init_step_length);
    void init_optimizer_amount_steps            (double const &init_amount_steps);
    void init_optimizer_chaotic_coeff           (double const &init_chaotic_coeff);
    void init_optimizer_chaotic_reduce_coeff    (double const &init_chaotic_reduce_coeff);
    void init_optimizer_alpha                   (double const &init_alpha);
    void init_optimizer_step_length_wo_recalc_chaotic_reduce_coeff (double const &init_step_length);

    void init_optimizer_set_amount_chaotic_func (unsigned const& amount_chaotic_functions);


    void init_chaotic(std::vector<std::vector<double> > const &init_initial_conditions, double const &init_step_length);
    void init_chaotic(double const &init_step_length);
    ////////////        END Initialize function
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    std::vector<std::vector<double> > result_take()  { return res; }
    bool result_write_to_file(const char* file_name) { return write_to_file(file_name, res); }

    void run_optimization();
    void run_optimization(unsigned const &init_amount_steps);
    void run_optimization(std::vector<double> const &init_initial_conditions);
    void run_optimization(double const &init_step_length, unsigned const &init_amount_steps);
    void run_optimization(std::vector<double> const &init_initial_conditions, double const &init_step_length, unsigned const &init_amount_steps);

    void recalc_chaotic_reduce_coeff() { chaotic_reduce_coeff = 1 - step_length / 100.0; }

//    double df_gen(double x, double h);
//
//    double func(double x);

    bool write_func_to_file(double x_begin, double x_end, unsigned steps, const char* file_name);

    bool write_chaos_to_file(const char* file_name);

private:
    bool isInitialConditionsHasSameDimentions(std::vector<std::vector<double> > const &init_initial_conditions);


//    std::vector<baseODE45*>       chaos_fuction;
//    baseODE45*                  chaos_fuction;
    std::vector<baseODE45*>     chaos_fuctions;
    OptimizedFunc               *optimized_function;

    std::vector<std::vector<double> > initial_conditions;

    double chaotic_coeff            {10};
    double chaotic_reduce_coeff     {0.999};
    double alpha                    {0.5};
};


#endif /* CPP_TCNN_OPT_FUNCTION_FUNCTIONS_TCNN_OPT_FUNCTION_H_ */

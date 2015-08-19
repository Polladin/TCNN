/*
 * opt_function.cpp
 *
 *  Created on: Aug 19, 2015
 *      Author: akukushk
 */

#include <vector>

#include "dll_opt_function.h"
#include "../../TCNN/opt_function/test/cmd_line_interface.h"


void optFuncSetInitialConditionByArgvDLL(TCNN_opt_function* optFunc, int argc, char* argv[])
{
    CLI_opt_func cli;

    cli.parse_cli(argc, argv);

    optFunc->init_optimizer_alpha(cli.alpha);
    optFunc->init_optimizer_amount_steps(cli.steps);
    optFunc->init_optimizer_step_length(cli.step_len);
    optFunc->init_optimizer_chaotic_coeff(cli.chaotic_coeff);
    optFunc->init_optimizer_chaotic_reduce_coeff(cli.chaotic_reduce);

    optFunc->init_optimizer_fuction(createFuncToOptimize(cli.function_to_optimize));

    if (cli.initial_condition.size())
    {
        optFunc->init_optimizer_initial_conditions(cli.initial_condition);
        optFunc->init_optimizer_set_amount_chaotic_func(cli.initial_condition.size()-1);
    }
}


void optFuncTakeResultDLL(TCNN_opt_function* optFunc, double *array)
{
    std::vector<std::vector<double> > res = optFunc->result_take();

    unsigned const amount_rows = res.size();

    for (unsigned row = 0; row < res.size(); ++row)
    {
        for (unsigned col = 0; col < res[row].size(); ++col)
        {
            array[col * amount_rows + row] = res[row][col];
        }
    }
}

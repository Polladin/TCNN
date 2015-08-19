/*
 * opt_func_shared_lib.cpp
 *
 *  Created on: Aug 19, 2015
 *      Author: akukushk
 */


#include "opt_func_shared_lib.h"

int opt_func_like_main(int argc, char* argv[])
{

    DISP_LOG_LVL = LI;
    LOG_MODE = ALL;

    std::cout << "Test for function optimization has been started\n";

    CLI_opt_func cli;

    cli.parse_cli(argc, argv);

    TCNN_opt_function testFunc(2);

    testFunc.init_optimizer_alpha(cli.alpha);
    testFunc.init_optimizer_chaotic_coeff(cli.chaotic_coeff);
    testFunc.init_optimizer_chaotic_reduce_coeff(cli.chaotic_reduce);

    testFunc.init_optimizer_fuction(createFuncToOptimize(cli.function_to_optimize));
    if (cli.initial_condition.size())
        testFunc.init_optimizer_initial_conditions(cli.initial_condition);

    std::vector<double> init;
    init.push_back(0);
    init.push_back(-0.5);

    if (   cli.function_to_optimize == eFunctionsToOptimize::FUNC_3_3D
        || cli.function_to_optimize == eFunctionsToOptimize::FUNC_4_3D)
    {
        init.push_back(-0.3);
    }

    if (cli.initial_condition.size())
    {
        testFunc.run_optimization(cli.step_len, cli.steps);
    }
    else
    {
        testFunc.run_optimization(init, cli.step_len, cli.steps);
    }


    testFunc.write_chaos_to_file("chaos.log");
    testFunc.result_write_to_file("opt_func_res.log");

    if (   cli.function_to_optimize == eFunctionsToOptimize::FUNC_1_2D
        || cli.function_to_optimize == eFunctionsToOptimize::FUNC_2_2D)
    {
        testFunc.write_func_to_file(-1.0, 3.5, 1000, "function.log");
    }

    cli.disp();

    std::cout << "Cpp code is done\n";
    return 0;
}

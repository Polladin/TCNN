/*
 * opt_func_test.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: alex
 */

#if 1

#include <string.h>
#include <stdlib.h>

#include "../../../common/debugLog/debugLog.h"
#include "../TCNN_opt_function.h"
#include "../../chaotic/chaotic.h"
#include "../../../common/ODE45/ODE45.h"
#include "../../../common/common.h"

const double DEFAULT_STEPS          = 10;
const double DEFAULT_STEP_LENGTH    = 0.1;
const double DEFAULT_ALPHA          = 0.5;
const double DEFAULT_CHAOTIC_COEFF  = 10;
const double DEFAULT_CHAOTIC_REDUCE = 0.999;

char buf[255];

int main(int argc, char* argv[])
{

    DISP_LOG_LVL = LI;
    LOG_MODE = ALL;

    std::cout << "Test for function optimization has been started\n";

    double        steps = 0
                , step_len = 0
                , alpha = 0
                , chaotic_coeff = 0
                , chaotic_reduce = 0;

    for (int i = 1; i < argc; ++i)
    {
        LM(LD, (argv[i]))

        if (strcmp(argv[i],"--steps") == 0 && (i+1 < argc))
        {
            steps = atof(argv[++i]);
            LM(LI, "Set steps: " << steps);
        }
        else if (strcmp(argv[i],"--step_len") == 0 && (i+1 < argc))
        {
            step_len = atof(argv[++i]);
            LM(LI, "Set step length: " << step_len);
        }
        else if (strcmp(argv[i],"--alpha") == 0 && (i+1 < argc))
        {
            alpha = atof(argv[++i]);
            LM(LI, "alpha: " << alpha);
        }
        else if (strcmp(argv[i],"--chaotic_coeff") == 0 && (i+1 < argc))
        {
            chaotic_coeff = atof(argv[++i]);
            LM(LI, "chaotic_coeff: " << chaotic_coeff);
        }
        else if (strcmp(argv[i],"--chaotic_reduce") == 0 && (i+1 < argc))
        {
            chaotic_reduce = atof(argv[++i]);
            LM(LI, "chaotic_reduce: " << chaotic_reduce);
        }
    }

    if (steps           == 0) steps         = DEFAULT_STEPS;
    if (step_len        == 0) step_len      = DEFAULT_STEP_LENGTH;
    if (alpha           == 0) alpha         = DEFAULT_ALPHA;
    if (chaotic_coeff   == 0) chaotic_coeff = DEFAULT_CHAOTIC_COEFF;
    if (chaotic_reduce  == 0) chaotic_reduce= DEFAULT_CHAOTIC_REDUCE;

//    baseODE45 chaos(new Chaotic);
//    std::vector<double> X;
//    X.push_back(0);
//    X.push_back(-0.1);
//    X.push_back(0);
//    X.push_back(0);
//    chaos.solve(X, step_len, steps);
//    write_to_file("chaos_test.log", chaos.result_take());

//    TCNN_opt_function testFunc(1);
//
//    std::vector<double> init;
//    init.push_back(0);
//    init.push_back(-1);
//
//    testFunc.init_optimizer_alpha(alpha);
//    testFunc.init_optimizer_chaotic_coeff(chaotic_coeff);
//    testFunc.init_optimizer_chaotic_reduce_coeff(chaotic_reduce);
//
//    testFunc.run_optimization(init, step_len, steps);
//
//    testFunc.result_write_to_file("opt_func_res.log");
//    testFunc.write_chaos_to_file("chaos.log");
//    testFunc.write_func_to_file(-1.0, 3.5, 1000, "function.log");

    TCNN_opt_function testFunc(2);

    testFunc.init_optimizer_alpha(alpha);
    testFunc.init_optimizer_chaotic_coeff(chaotic_coeff);
    testFunc.init_optimizer_chaotic_reduce_coeff(chaotic_reduce);

    testFunc.init_optimizer_fuction(new OptimizedFunc_4);

    std::vector<double> init;
    init.push_back(0);
    init.push_back(-0.5);
    init.push_back(-0.3);

    testFunc.run_optimization(init, step_len, steps);

    testFunc.write_chaos_to_file("chaos.log");
    testFunc.result_write_to_file("opt_func_res.log");

    std::cout << "Cpp code is done\n";
    return 0;
}

#endif

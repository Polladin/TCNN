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

char buf[255];

int main(int argc, char* argv[])
{

    DISP_LOG_LVL = LD;
    LOG_MODE = ALL;

    std::cout << "Test for function optimization has been started\n";

    double steps = 0;
    double step_len = 0;

    for (int i = 1; i < argc; ++i)
    {
        LM(LD, argv[i])

        if (strcmp(argv[i],"--steps") == 0 && (i+1 < argc))
        {
            steps = atof(argv[++i]);

            tmp_log_ostringstream.clear();
            tmp_log_ostringstream << "Set steps: " << steps;
            LM(LI, tmp_log_ostringstream.str());
//            LM(LI, "Set steps: " + std::to_string(steps));
        }
        else if (strcmp(argv[i],"--step_len") == 0 && (i+1 < argc))
        {
            step_len = atof(argv[++i]);

            tmp_log_ostringstream.clear();
            tmp_log_ostringstream <<"Set step length: " << step_len;
//            LM(LI, "Set step length: " + std::to_string(step_len));
        }
    }

    if (steps    == 0) steps    = DEFAULT_STEPS;
    if (step_len == 0) step_len = DEFAULT_STEP_LENGTH;

//    baseODE45 chaos(new Chaotic);
//    std::vector<double> X;
//    X.push_back(0);
//    X.push_back(-0.1);
//    X.push_back(0);
//    X.push_back(0);
//    chaos.solve(X, step_len, steps);
//    write_to_file("chaos_test.log", chaos.result_take());

    TCNN_opt_function testFunc;

    std::vector<double> init;
    init.push_back(0);
    init.push_back(-1);

    testFunc.run_optimization(init, step_len, steps);

    testFunc.result_write_to_file("opt_func_res.log");
    testFunc.write_chaos_to_file("chaos.log");
    testFunc.write_func_to_file(-1.0, 3.5, 1000, "function.log");

    std::cout << "Cpp code is done\n";
    return 0;
}

#endif

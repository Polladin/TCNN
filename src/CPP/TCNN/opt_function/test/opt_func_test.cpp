/*
 * opt_func_test.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: alex
 */

#include <string.h>

#include "../../../common/debugLog/debugLog.h"
#include "../functions/TCNN_opt_function.h"
#include "../chaotic/chaotic.h"

const double DEFAULT_STEPS          = 10;
const double DEFAULT_STEP_LENGTH    = 0.1;

char buf[255];

int main(int argc, char* argv[])
{

    DISP_LOG_LVL = LI;
    LOG_MODE = ALL;


    double steps = 0;
    double step_len = 0;

    for (int i = 1; i < argc; ++i)
    {
        LM(LD, argv[i])

        if (strcmp(argv[i],"--steps") == 0 && (i+1 < argc))
        {
            steps = atof(argv[++i]);
            LM(LI, "Set steps: " + std::to_string(steps));
        }
        else if (strcmp(argv[i],"--step_len") == 0 && (i+1 < argc))
        {
            step_len = atof(argv[++i]);
            LM(LI, "Set step length: " + std::to_string(step_len));
        }
    }

    if (steps    == 0) steps    = DEFAULT_STEPS;
    if (step_len == 0) step_len = DEFAULT_STEP_LENGTH;

    TCNN_opt_function testFunc(step_len);

    std::vector<double> init;
    init.push_back(0);
    init.push_back(-1);

//    testFunc.write_func_to_file(-1.0, 3.5, 10000, "function.log");

    std::vector<std::vector<double> > res;
    res = testFunc.run_ode(init, step_len, steps);

    std::vector<double> X;
    X.push_back(0);
    X.push_back(-0.1);
    X.push_back(0);
    X.push_back(0);

    //testFunc.chaos_fuction.run_ode(X, 0.1, steps);

    testFunc.write_result_in_file("opt_func_res.log");
    testFunc.write_chaos_to_file("chaos.log");
    testFunc.write_func_to_file(-1.0, 3.5, 1000, "function.log");

//    unsigned step_num = 0;
//    for(auto const &str : res)
//    {
//        LM(LD, "step " + std::to_string(step_num++))
//
//        for(auto const &row : str)
//        {
//            sprintf(buf, "\t row: %.15f", row);
////            LM(LD, std::string("\t row: ") + std::to_string(row));
//            LM(LD, buf);
//        }
//    }
}

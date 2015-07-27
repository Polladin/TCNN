/*
 * opt_func_test.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: alex
 */

#include "../../../common/debugLog/debugLog.h"
#include "../functions/TCNN_opt_function.h"


char buf[255];

int main()
{
    TCNN_opt_function testFunc;

    std::vector<double> init;
    init.push_back(0);
    init.push_back(0);

    std::vector<std::vector<double> > res;
    res = testFunc.run_ode(init, 0.1, 100);

    unsigned step_num = 0;
    for(auto const &str : res)
    {
        LM(LD, "step " + std::to_string(step_num++))

        for(auto const &row : str)
        {
            sprintf(buf, "\t row: %.15f", row);
//            LM(LD, std::string("\t row: ") + std::to_string(row));
            LM(LD, buf);
        }
    }
}

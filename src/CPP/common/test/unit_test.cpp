/*
 * unit_test.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: alex
 */

#include <stdio.h>
#include <string.h>

#include "../ODE45/ODE45.h"
#include "../debugLog/debugLog.h"

const double DEFAULT_STEPS          = 10;
const double DEFAULT_STEP_LENGTH    = 0.1;

char buf[255];

class testODE45 : public ODE45
{

public:

    virtual std::vector<double> calc_func(std::vector<double> X)
    {
        std::vector<double> dX(X.size());

        dX[0] = 1;
        dX[1] = X[2];
        dX[2] = X[3];
        dX[3] = (-0.44 * X[3] - 2 * X[2] + (X[1] * X[1] - 1)); //return (-0.44 * z - 2 * y + (x * x - 1)); //func_dE(z);
//        dX[0] = 1;
//        dX[1] = X[1];

        return dX;
    }
};

int main(int argc, char* argv[])
{
    testODE45 solver;
    double steps = 0;
    double step_len = 0;

    DISP_LOG_LVL = LD;
    LOG_MODE = ALL;

    for (int i = 1; i < argc; ++i)
    {
        LM(LD, argv[i])

        if (strcmp(argv[i],"--steps") == 0 && (i+1 < argc))
        {
            steps = atof(argv[++i]);
            LM(LD, "Set steps: " + std::to_string(steps));
        }
        else if (strcmp(argv[i],"--step_len") == 0 && (i+1 < argc))
        {
            step_len = atof(argv[++i]);
            LM(LD, "Set step length: " + std::to_string(step_len));
        }
    }

    std::to_string(steps);

    if (steps    == 0) steps    = DEFAULT_STEPS;
    if (step_len == 0) step_len = DEFAULT_STEP_LENGTH;

    LM(LD, "Unit test:");

    std::vector<double> init;
    init.push_back(0);
    init.push_back(-0.1);
    init.push_back(0);
    init.push_back(0);

    std::vector<std::vector<double> > res;
    res = solver.run_ode(init, step_len, steps);

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

    solver.write_result_in_file("unit_test.log"); //"/home/alex/CProject_mars/TCNN/build/result/unit_test.log");
}

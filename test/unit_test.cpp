/*
 * unit_test.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: alex
 */

#include <stdio.h>

#include "../src/ODE45/ODE45.h"
#include "../src/debugLog.h"

char buf[255];

class testODE45 : public ODE45
{

public:

    virtual std::vector<double> calc_func(std::vector<double> X)
    {
        std::vector<double> dX(X.size());

        dX[0] = 1;
        dX[1] = X[1];

        return dX;
    }
};

int main()
{
    testODE45 solver;

    LM(LD, "Unit test:");

    std::vector<double> init;
    init.push_back(0);
    init.push_back(1);

    std::vector<std::vector<double> > res;
    res = solver.run_ode(init, 0.1, 10);

    unsigned step_num = 0;
    for(auto const &str : res)
    {
        LM(LD, "step " + std::to_string(step_num++))

        for(auto const &row : str)
        {
            sprintf(buf, "\t row: %.15f", row);
//            LM(LD, std::string("\t row: ") + std::to_string(row));
            LM(LD, buf);
            std::to_string(row);
        }
    }

    solver.write_result_in_file("result/unit_test.log");
}

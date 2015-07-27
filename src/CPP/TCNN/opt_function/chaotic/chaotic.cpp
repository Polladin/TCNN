/*
 * chaotic.cpp
 *
 *  Created on: Jul 27, 2015
 *      Author: alex
 */

#include "chaotic.h"


std::vector<double> Chaotic::calc_func(std::vector<double> X)
{
    std::vector<double> dX(X.size());

    dX[0] = 1;
    dX[1] = X[2];
    dX[2] = X[3];
    dX[3] = (-0.44 * X[3] - 2 * X[2] + (X[1] * X[1] - 1)); //return (-0.44 * z - 2 * y + (x * x - 1)); //func_dE(z);

    return dX;
}


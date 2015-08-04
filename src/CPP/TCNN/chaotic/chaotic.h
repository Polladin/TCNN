/*
 * chaotic.h
 *
 *  Created on: Jul 27, 2015
 *      Author: alex
 */

#ifndef CPP_TCNN_OPT_FUNCTION_CHAOTIC_CHAOTIC_H_
#define CPP_TCNN_OPT_FUNCTION_CHAOTIC_CHAOTIC_H_

#include <vector>

#include "../../common/ODE45/ODE45.h"


class Chaotic1 : public baseODE45
{
public:

    virtual std::vector<double> calcFunc(std::vector<double> const &X)
    {
        std::vector<double> dX(X.size());

        dX[0] = 1;
        dX[1] = X[2];
        dX[2] = X[3];
        dX[3] = (-0.44 * X[3] - 2 * X[2] + (X[1] * X[1] - 1)); //return (-0.44 * z - 2 * y + (x * x - 1)); //func_dE(z);

        return dX;
    }
};


#endif /* CPP_TCNN_OPT_FUNCTION_CHAOTIC_CHAOTIC_H_ */

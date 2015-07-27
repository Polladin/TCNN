/*
 * chaotic.h
 *
 *  Created on: Jul 27, 2015
 *      Author: alex
 */

#ifndef CPP_TCNN_OPT_FUNCTION_CHAOTIC_CHAOTIC_H_
#define CPP_TCNN_OPT_FUNCTION_CHAOTIC_CHAOTIC_H_

#include <vector>

#include "../../../common/ODE45/ODE45.h"

class Chaotic : public ODE45
{

    virtual std::vector<double> calc_func(std::vector<double> X);

};

#endif /* CPP_TCNN_OPT_FUNCTION_CHAOTIC_CHAOTIC_H_ */

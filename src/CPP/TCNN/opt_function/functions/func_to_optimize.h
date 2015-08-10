/*
 * func_to_optimize.h
 *
 *  Created on: Aug 4, 2015
 *      Author: akukushk
 */

#ifndef FUNC_TO_OPTIMIZE_H_
#define FUNC_TO_OPTIMIZE_H_

#include "../../../common/common.h"
#include <cmath>

class OptimizedFunc
{
public:
    OptimizedFunc() {}
    virtual ~OptimizedFunc() {}

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Pure virtual method to get function's value
    virtual double fVal(std::vector<double> X) = 0;
    ////////////        END Pure virtual method to get function's value
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////        Function derivative
    double dF(std::vector<double> X, unsigned dim, double h);
    ////////////        END Function derivative
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:

    std::vector<double> vectorSummOneDim(std::vector<double> X, unsigned dim, double val);

    //deltaX to find derivative
    double deltaX    {0.00001};
};





/*
 *      Function:
 *                  (X-0.9)^2 + cos(3*PI*(X-0.9))
 */
class OptimizedFunc_1 : public OptimizedFunc
{
    virtual double fVal(std::vector<double> X)
    {
            return ((X[1]-0.9)-0.2)*((X[1]-0.9)-0.2) + std::cos(3.0*PI*(X[1]-0.9));
    }
};



/*
 *      Function:
 *                  (X-0.5)^2
 */
class OptimizedFunc_2 : public OptimizedFunc
{
    virtual double fVal(std::vector<double> X)
    {
        return (X[1]-0.5)*(X[1]-0.5);
    }
};



/*
 *     3D Function:
 *                  -20.0*exp(-0.2*sqrt(0.5*(X0^2+X1^2))) - exp(0.5*(cos(2*PI*X0)+cos(2*PI*X[1]))) + exp(1) + 20;
 */
class OptimizedFunc_3 : public OptimizedFunc
{
    virtual double fVal(std::vector<double> X)
    {
        return -20.0*std::exp(-0.2*std::sqrt(0.5*(X[1]*X[1]+X[2]*X[2]))) - std::exp(0.5*(std::cos(2.0*PI*X[1])+std::cos(2.0*PI*X[2]))) + std::exp(1) + 20;
    }
};



/*
 *     3D Function:
 *                  sin^2(3*PI*X) + (X-1)^2 * (1+sin^2(3*PI*Y)) + (Y-1)^2 * (1+sin(2*PI*Y))
 */
class OptimizedFunc_4 : public OptimizedFunc
{
    virtual double fVal(std::vector<double> X)
    {
        return std::sin(3*PI*X[1])*std::sin(3*PI*X[1])
                + (X[1]-1)*(X[1]-1) * (1 + std::sin(3*PI*X[2])*std::sin(3*PI*X[2]))
                + (X[2]-1)*(X[2]-1) * (1 + std::sin(2*PI*X[2])*std::sin(2*PI*X[2]));
    }
};




#endif /* FUNC_TO_OPTIMIZE_H_ */

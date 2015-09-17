/*
 * func_to_optimize.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: akukushk
 */


#include "func_to_optimize.h"

double OptimizedFunc::dF(std::vector<double> X, unsigned dim, double h)
{
    return (  -137.0 * fVal(X) + 300.0 * fVal(vectorSummOneDim(X,dim,h)) - 300.0 * fVal(vectorSummOneDim(X,dim,2.0*h))
              + 200.0 * fVal(vectorSummOneDim(X,dim,3.0*h)) - 75.0 * fVal(vectorSummOneDim(X,dim,4.0*h)) + 12.0 * fVal(vectorSummOneDim(X,dim,5.0*h))
           ) / (60 * h);
}


std::vector<double> OptimizedFunc::vectorSummOneDim(std::vector<double> X, unsigned const &dim, double const &val)
{
    X[dim] += val;

    return X;
}


OptimizedFunc* createFuncToOptimize(eFunctionsToOptimize const &func, unsigned dimension)
{
    switch(func)
    {
    case eFunctionsToOptimize::FUNC_1_2D:
        return new OptimizedFunc_1;

    case eFunctionsToOptimize::FUNC_2_2D:
        return new OptimizedFunc_2;

    case eFunctionsToOptimize::FUNC_3_3D:
        return new OptimizedFunc_3;

    case eFunctionsToOptimize::FUNC_4_3D:
        return new OptimizedFunc_4;

    case eFunctionsToOptimize::FUNC_5_ND:
        return new OptimizedFunc_5(dimension);

    case eFunctionsToOptimize::FUNC_6_ND:
        return new OptimizedFunc_6(dimension);

    case eFunctionsToOptimize::FUNC_7_ND:
        return new OptimizedFunc_7(dimension);

    case eFunctionsToOptimize::FUNC_8_ND:
        return new OptimizedFunc_8(dimension);
    default:
        return nullptr;
    }
}


char const* toString(eFunctionsToOptimize func)
{
    switch(func)
    {
    case eFunctionsToOptimize::NONE:
        return "NONE";

    case eFunctionsToOptimize::FUNC_1_2D:
        return "FUNC_1_2D";

    case eFunctionsToOptimize::FUNC_2_2D:
        return "FUNC_2_2D";

    case eFunctionsToOptimize::FUNC_3_3D:
        return "FUNC_3_3D";

    case eFunctionsToOptimize::FUNC_4_3D:
        return "FUNC_4_3D";

    case eFunctionsToOptimize::FUNC_5_ND:
        return "Rastrigin function: f(x) = 10n + Sum(x(i)^2 - 10cos(2pi*x(i)))";

    case eFunctionsToOptimize::FUNC_6_ND:
        return "Ndim func: f(x) = Sum((x(i))^2 - cos(3*PI*x(i)))";

    case eFunctionsToOptimize::FUNC_7_ND:
        return "Schwefel function: f(x) = Sum(-x(i)*sin(sqrt(abs(x(i)))))";

    case eFunctionsToOptimize::FUNC_8_ND:
        return "Griewankg function: f(x) = Sum(x(i)^2) / 4000 - Prod(cos(x(i)/sqrt(i))) + 1";

    case eFunctionsToOptimize::THE_LAST:
        return "THE_LAST";

    default:
        return "NOT FOUND";
    }
}

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


std::vector<double> OptimizedFunc::vectorSummOneDim(std::vector<double> X, unsigned dim, double val)
{
    X[dim] += val;

    return X;
}


OptimizedFunc* createFuncToOptimize(eFunctionsToOptimize const &func)
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
    default:
        return nullptr;
    }
}

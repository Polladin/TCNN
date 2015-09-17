/*
 * func_to_optimize.h
 *
 *  Created on: Aug 4, 2015
 *      Author: akukushk
 */

#ifndef FUNC_TO_OPTIMIZE_H_
#define FUNC_TO_OPTIMIZE_H_

#include "../../../common/common.h"
#include "../../../common/debugLog/debugLog.h"
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

    std::vector<double> vectorSummOneDim(std::vector<double> X, unsigned const &dim, double const& val);

    //deltaX to find derivative
    double deltaX    {0.00001};
};



enum class eFunctionsToOptimize
{
      NONE
    , FUNC_1_2D
    , FUNC_2_2D
    , FUNC_3_3D
    , FUNC_4_3D
    , FUNC_5_ND     //Rastrigin function:       f(x) = 10n + Sum(x(i)^2 - 10cos(2pi*x(i)))
    , FUNC_6_ND     //Ndim func:                f(x) = Sum((x(i))^2 - cos(3*PI*x(i)))
    , FUNC_7_ND     //Schwefel function:        f(x) = Sum(-x(i)*sin(sqrt(abs(x(i)))))
    , FUNC_8_ND     //Griewankg function:       f(x) = Sum(x(i)^2) / 4000 - Prod(cos(x(i)/sqrt(i))) + 1
    , THE_LAST
};

char const* toString(eFunctionsToOptimize func);

OptimizedFunc* createFuncToOptimize(eFunctionsToOptimize const &func, unsigned dimension = 1);


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


/*
 *     N dimensions Function:
 *
 *     Rastrigin function:
 *                  f(x) = 10n + Sum(x(i)^2 - 10cos(2pi*x(i)))
 *
 *          Global min:
 *                  f(x) = 0 x(i) = 0
 */
class OptimizedFunc_5 : public OptimizedFunc
{
public:
    OptimizedFunc_5(unsigned init_dimension): dimension(init_dimension) {}

    OptimizedFunc_5() {}


private:
    virtual double fVal(std::vector<double> X)
    {
        double res = 10.0 * dimension;

        for(unsigned i = 1; i <= dimension; ++i)
        {
            res += X[i] * X[i] - 10 * std::cos(2 * PI * X[i]);
        }

        return res;
    }

    unsigned dimension {1};
};



/*
 *   N dimensions  Function:
 *                  f(x) = Sum((x(i))^2 - cos(3*PI*x(i)))
 *
 *          Global min:
 *                  f(x) = -1*N x(i) = 0
 */
class OptimizedFunc_6 : public OptimizedFunc
{
public:

    OptimizedFunc_6(unsigned init_dimension): dimension(init_dimension) {}

    OptimizedFunc_6() {}

private:

    virtual double fVal(std::vector<double> X)
    {
        double res = 0;

        for(unsigned i = 1; i <= dimension; ++i)
        {
            res += X[i]*X[i] - std::cos(3.0*PI*X[i]);
        }

        return res;
    }

    unsigned dimension {1};
};



/*
 *   N dimensions  Function:
 *
 *      Schwefel function:
 *                  f(x) = Sum(-x(i)*sin(sqrt(abs(x(i)))))
 *
  *          Global min:
 *                  f(x) = -N * 418.9829 x(i) = 420.9687
 */
class OptimizedFunc_7 : public OptimizedFunc
{
public:

    OptimizedFunc_7(unsigned init_dimension): dimension(init_dimension) {}

    OptimizedFunc_7() {}

private:

    virtual double fVal(std::vector<double> X)
    {
        double res = 0;

        for(unsigned i = 1; i <= dimension; ++i)
        {
            res += -X[i] * std::sin(std::sqrt(std::abs(X[i])));
        }

        return res;
    }

    unsigned dimension {1};
};


/*
 *   N dimensions  Function:
 *
 *      Griewankg function:
 *                  f(x) = Sum(x(i)^2) / 4000 - Prod(cos(x(i)/sqrt(i))) + 1
 *
  *          Global min:
 *                  f(x) = 0 x(i) = 0
 */
class OptimizedFunc_8 : public OptimizedFunc
{
public:

    OptimizedFunc_8(unsigned init_dimension): dimension(init_dimension) {}

    OptimizedFunc_8() {}

private:

    virtual double fVal(std::vector<double> X)
    {
        double res_sum  = 0;
        double res_prod = 0;

        for(unsigned i = 1; i <= dimension; ++i)
        {
            res_sum += X[i] * X[i];
            res_prod *=  std::cos(X[i]/std::sqrt(i));
        }

        return res_sum / 4000.0 + res_prod + 1;
    }

    unsigned dimension {1};
};


#endif /* FUNC_TO_OPTIMIZE_H_ */

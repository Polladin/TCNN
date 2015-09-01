/*
 * TSPsolver.h
 *
 *  Created on: Sep 1, 2015
 *      Author: akukushk
 */

#ifndef TSPSOLVER_H_
#define TSPSOLVER_H_

#include <vector>

#include "../chaotic/chaotic.h"
#include "../../common/ODE45/ODE45.h"

class TSPsolver : public baseODE45
{

public:

    TSPsolver(unsigned cities, unsigned amount_col);

    ~TSPsolver()
    {
        for(int i = 0; i < chaos.size(); ++i)
        {
            for(int j = 0; j < chaos[i].size(); ++j)
            {
                delete chaos[i][j];
            }
        }
    }

    void init_chaotic(unsigned cities);
    void init_X_randomly(unsigned cities);
    void init_dist(unsigned amount_col);

    std::vector<double> calcFunc(std::vector<double> const &X);

    double dF(std::vector<double> const &X, unsigned neuron);

private:

    double get_by_index(std::vector<double> X, unsigned row, unsigned col);

    std::vector<std::vector<baseODE45*>>     chaos; //N x N   - chaotic for activation functions
    std::vector<double>                      X;     //N x N + 1 (time stamp)  activation functions
    std::vector<std::vector<double>>         dist;  //N x N  - distance between cities

    unsigned amount_cities   {0};
    unsigned offset_X        {1};

    double    W1             {0}
            , W2             {0};

    double chaotic_coeff            {10};
    double chaotic_reduce_coeff     {0.999};
    double alpha                    {0.5};
    double dist_one                 {1};
};



#endif /* TSPSOLVER_H_ */

/*
 * TSPsolver.cpp
 *
 *  Created on: Sep 1, 2015
 *      Author: akukushk
 */

#include <vector>
#include <fstream>
#include <cmath>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../common/debugLog/debugLog.h"
#include "../../common/common.h"

#include "TSPsolver.h"


TSPsolver::TSPsolver(unsigned cities, unsigned amount_col)
{
    amount_cities = cities;

    W1 = 0.5;
    W2 = 0.1;

    init_chaotic(cities);

    init_X_randomly(cities);

    init_dist(amount_col);

}


void TSPsolver::init_dist(unsigned amount_col)
{
    dist.resize(amount_cities, std::vector<double>(amount_cities));

    for (unsigned i = 0; i < amount_cities; ++i)
    {
        for (unsigned j = 0; j < amount_cities; ++j)
        {
            unsigned row_i = i / amount_col;
            unsigned col_i = i % amount_col;
            unsigned row_j = j / amount_col;
            unsigned col_j = j % amount_col;

            dist[i][j] = std::sqrt(static_cast<double>((row_i - row_j) * (row_i - row_j) + (col_i - col_j) * (col_i - col_j)));
        }
    }
}

void TSPsolver::init_X_randomly(unsigned cities)
{
    double rand_initial_cond;
    srand (time(0));

    X.resize(offset_X + cities*cities);

    for (unsigned i = 0; i < offset_X; ++i)
    {
        X[i] = 0;
    }

    for (int i=0; i<150; ++i)
    {
        rand_initial_cond = 2.0 * (static_cast<double>(rand())/RAND_MAX-0.5) * 0.2;
    }

    for (unsigned i = offset_X; i < cities * cities + offset_X; ++i)
    {
        rand_initial_cond = (static_cast<double>(rand())/RAND_MAX);
        X[i] = rand_initial_cond;
    }

    solve_init(X);
}


void TSPsolver::init_chaotic(unsigned cities)
{
    double rand_initial_cond;
    srand (time(0));

    for(auto elem : chaos)
    {
        for(auto *sub_elem : elem)
        {
            delete sub_elem;
        }
    }
    chaos.clear();

    for (int i=0; i<100; ++i)
    {
        rand_initial_cond = 2.0 * (static_cast<double>(rand())/RAND_MAX-0.5) * 0.2;
    }

    for (unsigned i = 0; i < cities; ++i)
    {
        std::vector<baseODE45*> city_row;

        for (unsigned j = 0; j < cities; ++j)
        {
            rand_initial_cond = 2.0 * (static_cast<double>(rand())/RAND_MAX-0.5) * 0.2;

            LM(LI, "rand initial cond: " << rand_initial_cond)

            std::vector<double> X;
            X.push_back(0);
            X.push_back(rand_initial_cond);
            X.push_back(0);
            X.push_back(0);

            city_row.push_back(new Chaotic1);
            city_row.back()->solve_init(X, step_length);
        }

        chaos.push_back(city_row);
        city_row.clear();
    }
}



std::vector<double> TSPsolver::calcFunc(std::vector<double> const &X)
{
    std::vector<double> dX(X.size());
    std::vector<double> chaoticValue;

    for (auto elem : chaos)
    {
        for (auto *p_chaos : elem)
        {
            std::vector<double> tmp = p_chaos->solve_get_next();
            chaoticValue.push_back(tmp[3]);
        }
    }

    dX[0] = 1;
    for (unsigned i = 1; i < X.size(); ++i)
    {
        dX[i] = chaotic_coeff*chaoticValue[(i-1)] - alpha * dF(X,i-1);
    }

    chaotic_coeff *= chaotic_reduce_coeff;

    return dX;
}


double TSPsolver::dF(std::vector<double> const &X, unsigned neuron)
{
    double   sum_1 = 0
            ,sum_2 = 0;

    unsigned num_neuron_row = neuron / amount_cities;
    unsigned num_neuron_col = neuron % amount_cities;

    unsigned next_city = (num_neuron_row == amount_cities-1) ? 0 : num_neuron_row - 1;
    unsigned prev_city = (num_neuron_row == 0) ? amount_cities-1 : num_neuron_row;

    for (unsigned row = 0; row < amount_cities; ++row)  //time dimension
    {
        sum_1 += (row != num_neuron_row) ? get_by_index(X, num_neuron_col, row) : 0;
    }

    for (unsigned col = 0; col < amount_cities; ++col)  //city dimension
    {
        sum_1 += (col != num_neuron_col) ? get_by_index(X, col, num_neuron_row) : 0;
        sum_2 += (col != num_neuron_col) ? dist[num_neuron_col][col] * (get_by_index(X, col, next_city) +  get_by_index(X, col ,prev_city)) : 0;
    }

   return -W1 * sum_1 - W2 * sum_2 + W1;
}



double TSPsolver::get_by_index(std::vector<double> X, unsigned col, unsigned row)
{
    return X[offset_X + row * amount_cities + col];
}







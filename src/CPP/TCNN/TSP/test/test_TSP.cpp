/*
 * test_TSP.cpp
 *
 *  Created on: Sep 1, 2015
 *      Author: akukushk
 */


#if 1


#include "../TSPsolver.h"


int main()
{

    TSPsolver obj(4,2);

    obj.solve(10);

    obj.result_write_to_file("D:\\TSP_res.log");

    return 0;
}



#endif

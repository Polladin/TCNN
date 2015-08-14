/*
 * cmd_line_interface.h
 *
 *  Created on: Aug 12, 2015
 *      Author: akukushk
 */

#ifndef CMD_LINE_INTERFACE_H_
#define CMD_LINE_INTERFACE_H_


#include "../functions/func_to_optimize.h"



const double DEFAULT_STEPS          = 10;
const double DEFAULT_STEP_LENGTH    = 0.1;
const double DEFAULT_ALPHA          = 0.5;
const double DEFAULT_CHAOTIC_COEFF  = 10;
const double DEFAULT_CHAOTIC_REDUCE = 0.999;

const int DEFAULT_OPT_FUNC     = static_cast<int>(eFunctionsToOptimize::FUNC_1_2D);


struct CLI_opt_func
{
    double        steps             {0}
                , step_len          {0}
                , alpha             {0}
                , chaotic_coeff     {0}
                , chaotic_reduce    {0};

    eFunctionsToOptimize function_to_optimize {eFunctionsToOptimize::FUNC_4_3D};

    void parse_cli(int argc, char* argv[]);

    void disp();
};



#endif /* CMD_LINE_INTERFACE_H_ */

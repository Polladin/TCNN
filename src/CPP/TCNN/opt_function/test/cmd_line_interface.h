/*
 * cmd_line_interface.h
 *
 *  Created on: Aug 12, 2015
 *      Author: akukushk
 */

#ifndef CMD_LINE_INTERFACE_H_
#define CMD_LINE_INTERFACE_H_

#include <vector>

#include "../functions/func_to_optimize.h"



const unsigned DEFAULT_STEPS                = 10;
const unsigned DEFAULT_DIMENSION            = 10;
const double DEFAULT_STEP_LENGTH            = 0.1;
const double DEFAULT_CHAOTIC_STEP_LENGTH    = 0.1;
const double DEFAULT_ALPHA                  = 0.5;
const double DEFAULT_CHAOTIC_COEFF          = 10;
const double DEFAULT_CHAOTIC_REDUCE         = 0.999;

const int DEFAULT_OPT_FUNC     = static_cast<int>(eFunctionsToOptimize::FUNC_1_2D);


struct CLI_opt_func
{
    unsigned      steps                 {DEFAULT_STEPS};
    unsigned      dimension             {DEFAULT_DIMENSION};

    double        step_len              {DEFAULT_STEP_LENGTH}
                , chaotic_step_len      {DEFAULT_CHAOTIC_STEP_LENGTH}
                , alpha                 {DEFAULT_ALPHA}
                , chaotic_coeff         {DEFAULT_CHAOTIC_COEFF}
                , chaotic_reduce        {DEFAULT_CHAOTIC_REDUCE};


    std::vector<double> initial_condition;

    eFunctionsToOptimize function_to_optimize {eFunctionsToOptimize::FUNC_4_3D};

    void parse_cli(int argc, char* argv[]);

    void disp();
};



#endif /* CMD_LINE_INTERFACE_H_ */

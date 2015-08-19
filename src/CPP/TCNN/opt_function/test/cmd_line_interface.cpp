/*
 * cmd_line_interface.cpp
 *
 *  Created on: Aug 14, 2015
 *      Author: akukushk
 */

#include <string.h>
#include <stdlib.h>
#include <cstring>

#include "../../../common/debugLog/debugLog.h"
#include "../functions/func_to_optimize.h"

#include "cmd_line_interface.h"

void CLI_opt_func::parse_cli(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        LM(LD, (argv[i]))

        if (strcmp(argv[i],"--steps") == 0 && (i+1 < argc))
        {
            steps = static_cast<unsigned>(atof(argv[++i]));
            LM(LI, "Set steps: " << steps);
        }
        else if (strcmp(argv[i],"--step_len") == 0 && (i+1 < argc))
        {
            step_len = atof(argv[++i]);
            LM(LI, "Set step length: " << step_len);
        }
        else if (strcmp(argv[i],"--alpha") == 0 && (i+1 < argc))
        {
            alpha = atof(argv[++i]);
            LM(LI, "alpha: " << alpha);
        }
        else if (strcmp(argv[i],"--chaotic_coeff") == 0 && (i+1 < argc))
        {
            chaotic_coeff = atof(argv[++i]);
            LM(LI, "chaotic_coeff: " << chaotic_coeff);
        }
        else if (strcmp(argv[i],"--chaotic_reduce") == 0 && (i+1 < argc))
        {
            chaotic_reduce = atof(argv[++i]);
            LM(LI, "chaotic_reduce: " << chaotic_reduce);
        }
        else if (strcmp(argv[i],"--function") == 0 && (i+1 < argc))
        {
            int __func = atoi(argv[++i]);
            LM(LI, "function: " << __func);
            if (   __func > static_cast<int>(eFunctionsToOptimize::NONE)
                && __func < static_cast<int>(eFunctionsToOptimize::THE_LAST) )
            {
                function_to_optimize = static_cast<eFunctionsToOptimize>(__func);
            }
            else
            {
                LM(LE, "function is not in valid range")
            }
        }
        else if (strcmp(argv[i],"--init_cond") == 0 && (i+1 < argc))
        {
           char* str = argv[++i];

           LM(LI, "Set Initial Condition")

           char * pch = strtok(str, ",");
           while (pch != NULL)
           {
               double init_cond_val = atof(pch);
               LM(LI, atof(pch));
               initial_condition.push_back(init_cond_val);

               pch = strtok (NULL, ",");
           }
        }
    }

    if (steps           == 0) steps         = DEFAULT_STEPS;
    if (step_len        == 0) step_len      = DEFAULT_STEP_LENGTH;
    if (alpha           == 0) alpha         = DEFAULT_ALPHA;
    if (chaotic_coeff   == 0) chaotic_coeff = DEFAULT_CHAOTIC_COEFF;
    if (chaotic_reduce  == 0) chaotic_reduce= DEFAULT_CHAOTIC_REDUCE;
}

double        steps             {0}
            , step_len          {0}
            , alpha             {0}
            , chaotic_coeff     {0}
            , chaotic_reduce    {0};

void CLI_opt_func::disp()
{
    LM(LI, "steps:" << steps);
    LM(LI, "step_len:" << step_len);
    LM(LI, "alpha:" << alpha);
    LM(LI, "chaotic_coeff:" << chaotic_coeff);
    LM(LI, "chaotic_reduce:" << chaotic_reduce);
    LM(LI, "function_to_optimize:" << toString(function_to_optimize));

}



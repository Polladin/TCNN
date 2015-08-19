/*
 * opt_function.h
 *
 *  Created on: Aug 19, 2015
 *      Author: akukushk
 */

#ifndef OPT_FUNCTION_H_
#define OPT_FUNCTION_H_

#include "../../TCNN/opt_function/TCNN_opt_function.h"


extern "C" {

    TCNN_opt_function* optFuncCreateDLL() { return new TCNN_opt_function(); }

    void optFuncSetInitialConditionByArgvDLL(TCNN_opt_function* optFunc, int argc, char* argv[]);

    void optFuncRunOptimizationDLL(TCNN_opt_function* optFunc) { optFunc->run_optimization(); }

    void optFuncWriteResultDLL(TCNN_opt_function* optFunc, char const* file_name) { optFunc->result_write_to_file(file_name); }

    void optFuncTakeResultDLL(TCNN_opt_function* optFunc, double *array);

    void optFuncDestroyObj(TCNN_opt_function* optFunc) { delete optFunc; }

    unsigned optFunctGetResultRows(TCNN_opt_function* optFunc) { return optFunc->resultRowsAmount(); }

    unsigned optFunctGetResultColumns(TCNN_opt_function* optFunc) { return optFunc->resultColumnsAmount(); }
}

#endif /* OPT_FUNCTION_H_ */

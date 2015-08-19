/*
 * opt_func_shared_lib.h
 *
 *  Created on: Aug 18, 2015
 *      Author: akukushk
 */

#ifndef OPT_FUNC_SHARED_LIB_H_
#define OPT_FUNC_SHARED_LIB_H_

#include "../../../common/debugLog/debugLog.h"
#include "../TCNN_opt_function.h"
#include "../../chaotic/chaotic.h"
#include "../../../common/ODE45/ODE45.h"
#include "../../../common/common.h"
#include "../functions/func_to_optimize.h"
#include "cmd_line_interface.h"

extern "C" {

    int opt_func_like_main(int argc, char* argv[]);

}


#endif /* OPT_FUNC_SHARED_LIB_H_ */

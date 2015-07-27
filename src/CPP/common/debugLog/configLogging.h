/*
 * configLogging.h
 *
 *  Created on: Jul 27, 2015
 *      Author: alex
 */

#ifndef CPP_COMMON_DEBUGLOG_CONFIGLOGGING_H_
#define CPP_COMMON_DEBUGLOG_CONFIGLOGGING_H_


dispLogMode     LOG_MODE = ALL;
log_lvl_const   DISP_LOG_LVL = LD;

const char* enabledFilesToLog[] =
{
           "unit_test.cpp"
         , "ODE45.cpp"
};

const char* disabledFilesToLog[] =
{
        "unit_test.cpp"
};

#endif /* CPP_COMMON_DEBUGLOG_CONFIGLOGGING_H_ */

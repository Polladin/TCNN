/*
 * debugLog.h
 *
 *  Created on: Jul 20, 2015
 *      Author: alex
 */

#ifndef DEBUGLOG_H_
#define DEBUGLOG_H_


#include <iostream>
#include <string>
#include <string.h>
#include <sstream>

enum dispLogMode
{
      ALL
    , ENABLED_LIST
    , DISABLED_LIST
};

enum log_lvl_const
{
      LD
    , LI
    , LW
    , LE
    , NONE_DISP_LOG
};

extern dispLogMode   LOG_MODE;
extern log_lvl_const DISP_LOG_LVL;
extern std::ostringstream tmp_log_ostringstream;

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define LM(lvl,str) logging::print_log(str, lvl, __FILENAME__, __LINE__);

namespace logging
{

const char* toString(log_lvl_const const &lvl);

void write_to_log(std::string const &str, unsigned const &lvl, const char* file, int const &line);

void print_log(std::string const &str, unsigned const &lvl, const char* file, int const &line);


}// end namespace logging

#endif /* DEBUGLOG_H_ */

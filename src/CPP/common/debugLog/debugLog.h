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

#define LM(lvl,str) logging::print_log(str, lvl, __FILE__, __LINE__);

enum log_lvl_const
{
    LD,
    LE,
    LI
};

namespace logging
{

const char* toString(log_lvl_const lvl);

void print_log(std::string str, unsigned lvl, const char* file, int line);


}// end namespace logging

#endif /* DEBUGLOG_H_ */

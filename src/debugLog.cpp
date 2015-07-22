/*
 * debugLog.cpp
 *
 *  Created on: Jul 20, 2015
 *      Author: alex
 */

#include "debugLog.h"


namespace logging
{

const char* toString(log_lvl_const lvl)
{
    switch(lvl)
    {
    case LD:
        return "DBG:";
    case LE:
        return "ERR:";
    case LI:
        return "INF:";
    default:
        return "unknown:";
    }
}


void print_log(std::string str, unsigned lvl, const char* file, int line)
{
    std::cout << file << " " << line << ":" <<toString(log_lvl_const(lvl)) << str << std::endl;
}

}// end namespace logging

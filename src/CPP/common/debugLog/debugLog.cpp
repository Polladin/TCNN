/*
 * debugLog.cpp
 *
 *  Created on: Jul 20, 2015
 *      Author: alex
 */

#include "debugLog.h"
#include "configLogging.h"

namespace logging
{

const char* toString(log_lvl_const const &lvl)
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


void write_to_log(std::string const &str, unsigned const &lvl, const char* file, int const &line)
{
    if (lvl >= DISP_LOG_LVL)
    {
        std::cout << file << "[" << line << "]:" <<toString(log_lvl_const(lvl)) << str << std::endl;
    }
}


inline bool is_in_enable_log_list(const char *file)
{
    for (auto f_name : enabledFilesToLog)
    {
        if (strcmp(f_name, file) == 0)
        {
            return true;
        }
    }
    return false;
}

inline bool is_not_in_disbled_log_list(const char *file)
{
    for (auto f_name : disabledFilesToLog)
    {
        if (strcmp(f_name, file) == 0)
        {
            return false;
        }
    }
    return true;
}


void print_log(std::string const &str, unsigned const &lvl, const char* file, int const &line)
{
    switch (LOG_MODE)
    {
    case ALL:
        write_to_log(str, lvl, file, line);
        break;

    case ENABLED_LIST:
        if (is_in_enable_log_list(file)) write_to_log(str, lvl, file, line);
        break;

    case DISABLED_LIST:
        if (is_not_in_disbled_log_list(file)) write_to_log(str, lvl, file, line);
        break;
    }

}

}// end namespace logging

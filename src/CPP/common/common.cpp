/*
 * common.cpp
 *
 *  Created on: Jul 30, 2015
 *      Author: akukushk
 */

#include <fstream>
#include <string>

#include "common.h"
#include "debugLog/debugLog.h"

bool write_to_file(const char* file_name, std::vector<std::vector<double> > const &data)
{
    try
    {
        std::ofstream file_out;
        file_out.open (file_name, std::ios::out );

        for(auto const &row : data)
        {
            for (auto const &elem : row)
            {
                file_out << elem << "\t";
            }
            file_out << "\n";
        }
    }
    catch(...)
    {
        LM(LE, "while writing to file " + std::string(file_name));
        return false;
    }

    return true;
}

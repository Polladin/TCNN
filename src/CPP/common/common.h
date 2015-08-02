/*
 * common.h
 *
 *  Created on: Jul 19, 2015
 *      Author: alex
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <vector>

const double PI = 3.14159265359;


bool write_to_file(const char* file_name, std::vector<std::vector<double> > const &data);


#endif /* SRC_COMMON_H_ */

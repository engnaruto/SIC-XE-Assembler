/*
 * Check.h
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#ifndef CHECK_H_
#define CHECK_H_
#include <iostream>
#include "pass1.h"
class Check {
public:
	bool checkSpaces(std::string str, int type);
	bool checkLabel(std::string label);
	int checkAtHash(std::string searchable);

};

#endif /* CHECK_H_ */

/*
 * OpInfo.h
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#ifndef OPINFO_H_
#define OPINFO_H_
#include <iostream>
#include "debug.cpp"
class OpInfo {
public:
	OpInfo();
	OpInfo(std::string operand, std::string format, std::string opcode);
	~OpInfo();
	std::string operand;
	std::string format;
	std::string opcode;
};

#endif /* OPINFO_H_ */

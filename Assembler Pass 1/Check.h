/*
 * Check.h
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#ifndef CHECK_H_
#define CHECK_H_
#include <iostream>
#include "Tables.h"
class Check {
public:
	bool checkSpaces(std::string str, int type);
	bool checkLabel(std::string label);
	int checkAtHash(std::string searchable);
	bool check(std::string operation);
	bool checkHexaNumber(std::string st);
	bool checkLabel(std::string label,
			std::map<std::string, std::string> labels);
	bool checkLabelAndNubmers(std::string label,
			std::map<std::string, std::string> labels);
	bool checkRegister(std::string str1, std::string str2,
			std::map<std::string, std::string> labels);
	bool checkRegister(std::string str1);
	bool checkNumber(std::string str);
	bool checkOperand(std::string operand,
			std::map<std::string, std::string> labels);
	bool checkOperationOperandMathcing(std::string operand,
			std::string operation);
	bool isNumber(std::string st);
};

#endif /* CHECK_H_ */

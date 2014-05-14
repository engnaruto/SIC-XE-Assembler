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
	Check(Tables &tables);
	~Check();
	std::string checkAll(std::string *label, std::string *operation,
			std::string *operand);
private:
	Tables tables;
	bool checkSpaces(std::string str, int type);
	bool checkLabel(std::string *label);
	bool checkOperation(std::string *operation);
	bool checkOperand(std::string *operand);
	int checkAtHash(std::string searchable);
	bool checkHexaNumber(std::string st);
	bool isatSymTable(std::string label);
	bool checkLabelAndNubmers(std::string label);
	bool checkRegister(std::string str1, std::string str2);
	bool checkRegister(std::string str1);
	bool checkOperationOperandMathcing(std::string operand,
			std::string operation);
	bool isNumber(std::string st);
	std::string trim(std::string input);
	std::string toLowerCase(std::string input) ;
}
;

#endif /* CHECK_H_ */

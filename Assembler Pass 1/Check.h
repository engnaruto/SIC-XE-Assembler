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
	std::string toLowerCase(std::string input);
private:
	Tables tables;
	bool checkSpaces(std::string str, int type);
	bool checkLabel(std::string *label, std::string *exception);
	bool checkOperation(std::string *operation, std::string *exception);
	bool checkOperand(std::string *operand, std::string *exception);
	bool checkOperationOperandMathcing(std::string operation,
			std::string operand, std::string *exception);
	int checkAtHash(std::string searchable);
	bool isHexaNumber(std::string st, std::string *exception);
	bool isatSymTable(std::string label);
	bool checkLabelAndNubmers(char c, std::string label,
			std::string *exception);
	bool checkRegister(std::string str1, std::string str2,
			std::string *exception);
	bool checkRegister(std::string str1);
	bool checkByte(std::string oper, std::string *exception);
	bool isNumber(std::string st);
	std::string trim(std::string input);
}
;

#endif /* CHECK_H_ */

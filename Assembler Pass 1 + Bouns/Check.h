/*
 * Check.h
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#ifndef CHECK_H_
#define CHECK_H_
#include <iostream>
#include "debug.cpp"
#include "Tables.h"
#include "FileOperations.h"
//class Tables;
class Check {
public:
	Check(Tables &tables);
	~Check();
	std::string checkAll(std::vector<std::string> arr ,std::string *label,
			std::string *operation, std::string *operand, std::string *comment);
	void split(std::string inputLine[], std::string *_label,
			std::string *_operation, std::string *_operand,
			std::string *_comment);
	std::string toLowerCase(std::string input);
	Tables getTables();
	bool checkOperation(std::string *operation, std::string *exception);
	bool checkLabel(std::string *label, std::string *exception);
	bool checkOperand(std::string *operand, std::string *exception);
	bool checkOperationOperandMathcing(std::string operation,
			std::string operand, std::string *exception);
private:
	Tables tables;
	bool checkSpaces(std::string str, int type);
	int checkAtHash(std::string searchable);
	bool checkHexaNumber(std::string st, std::string *exception);
	bool isatSymTable(std::string label);
	bool checkLabelAndNubmers(char c, std::string label,
			std::string *exception);
	bool checkRegister(std::string str1, std::string str2,
			std::string *exception);
	bool checkRegister(std::string str1);
	bool isNumber(std::string st);
	std::string trim(std::string input);
	void split(std::vector<std::string>arr, std::string *_label, std::string *_operation,
			std::string *_operand, std::string *_comment) ;
}
;

#endif /* CHECK_H_ */

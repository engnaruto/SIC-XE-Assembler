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
#include "LocCounter.h"
class Check {
public:
	Check(Tables *tables);
	~Check();
	std::string checkAll(std::string address, std::string *label,
			std::string *operation, std::string *operand, LocCounter*loc);
	std::string toLowerCase(std::string input);
	std::string trim(std::string input);
	void ORG(std::string operat, std::string oper, LocCounter loc,
			std::string *exception);
//	std::string EQU(std::string operat, std::string oper, LocCounter loc,
//			std::string * exception);
	void EQU(std::string operat, std::string oper, LocCounter loc,
			std::string * exception);
	std::string format(std::string operation, std::string operand,
			std::string address);
	std::string opCodeFor4(std::string operation, std::string operand,
			std::string address);
	std::string opCode(std::string operation, std::string operand,
			std::string address);

private:
	Tables *tables;
	bool checkSpaces(std::string str, int type);
	bool checkLabel(std::string address, std::string *label,
			std::string *exception);
	bool checkOperation(std::string *operation, std::string *exception);
	bool checkOperand(std::string *operand, std::string *exception);
	bool checkOperationOperandMatching(std::string operation,
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
	bool checkAddress(std::string st, std::string * exception);
//	bool isNumber(std::string st);
	std::string trim2(std::string input);
	bool isNumber(std::string st);
	int dec_to_binary(int dec);
	int binary_to_dec(int bin);
	int conHexaToDec(std::string s);
	std::string convertIntToString(int number);
	std::string dectoHex(int decimal);
	std::string regFormat(std::string operand);
	std::string regFormat2(std::string operand);
	std::string calcuteAddresse(std::string next_a, std::string *bp,
			std::string operand);
	bool validOperand(std::string operand);
	bool isNumberOperand(std::string st);
	std::string convDectoHex(int decNum, int r[]);
	bool checkDirectives(std::string operation, std::string operand,
			std::string *ob_directive);
	std::string evaluate(std::string oper, LocCounter loc,
			std::string *exception);
}
;

#endif /* CHECK_H_ */

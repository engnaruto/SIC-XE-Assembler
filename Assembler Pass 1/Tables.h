/*
 * pass1.h
 *
 *  Created on: May 14, 2014
 *      Author: Naruto
 */

#ifndef PASS1_H_
#define PASS1_H_
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include<string>
#include <exception>
#include <stdlib.h>
#include "FileOperations.h"
#include "OpInfo.h"
#include "debug.cpp"

class Tables {
public:
	Tables();
	~Tables();
	std::map<std::string, OpInfo> opTable;
	std::map<std::string, std::string> symTable;
	void loadHash();
	int getLength(std::string operation, std::string operand);
	std::string toLowerCase(std::string input);
private:
	std::vector<std::string> &split(const std::string &s, char delim,
			std::vector<std::string> &elems);
	std::vector<std::string> split(const std::string &s, char delim);
};
#endif /* PASS1_H_ */

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
#include <vector>
#include <fstream>
#include <sstream>
#include<string>
#include <exception>
#include "FileOperations.h"
#include "OpInfo.h"

class pass1 {
public:
	 std::map<std::string, OpInfo> opTable;
	 std::map<std::string, std::string> symTable;
private:
	std::vector<std::string> &split(const std::string &s, char delim,
			std::vector<std::string> &elems);
	std::vector<std::string> split(const std::string &s, char delim);
	int main(int argc, char **argv);
	void loadHash();

};

//std::map<std::string, OpInfo> pass1::opTable;
//std::map<std::string, std::string> pass1::symTable;
#endif /* PASS1_H_ */

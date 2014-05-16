/*
 * FileOperations.h
 *
 *  Created on: May 12, 2014
 *      Author: Naruto
 */

#ifndef FILEOPERATIONS_H_
#define FILEOPERATIONS_H_

#include<iostream>
#include <fstream>
//#include "Tables.h"
#include <vector>
//#include "Check.h"
#include "debug.cpp"
//#include <string>
//using namespace std;
//class Check;
class FileOperations {
public:
	 std::vector<std::string>arr;
	// Constructor/Destructor
//	FileOperations(std::string fileName);
	FileOperations(std::string fileName);
	~FileOperations();
	void use(std::string filename);
	//Reading Methods
	std::string readLine();
	std::string readLabel(std::string line);
	std::string readOperation(std::string line);
	std::string readOperand(std::string line);
	std::string readComment(std::string line);
	//Writing Methods
	void writeFirst();
	void writeAll(int lineNo, std::string address, std::string label,
			std::string operation, std::string operand, std::string comment);
	void writeLine(std::string line);
	void writeLabel(std::string label);
	void writeOperation(std::string operation);
	void writeOperand(std::string operand);
	void writeComment(std::string comment);
	void writeEnter();
	// Other Methods
	bool eof();
//	void enableDebug();
//	void disableDebug();
	void close();
private:

//	Check Check::*check;
	std::ifstream in;
	std::ofstream out;

	std::string removeSpaces(std::string line);
	void splitBySpace(std::string line);
	void split(std::string inputLine[], std::string *_label,
			std::string *_operation, std::string *_operand,
			std::string *_comment);

};

#endif /* FILEOPERATIONS_H_ */

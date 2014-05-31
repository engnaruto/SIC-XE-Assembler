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
#include "debug.cpp"
#include <sstream>
#include <vector>
//using namespace std;

class FileOperations {
public:
	// Constructor/Destructor
	FileOperations(std::string fileName);
	~FileOperations();
	bool use(std::string filename);
	bool writeIn(std::string filename);
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
	void writeAll(std::string address, std::string objectCode,
			std::string label, std::string operation, std::string operand);
	std::string writeError(std::string address, std::string objectCode,
			std::string label, std::string operation, std::string operand);
	void writeImmidiate(std::string address, std::string label,
			std::string operation, std::string operand);
	void writeLine(std::string line);
	void writeTxtRecord(std::string strtAddress, std::string length,
			std::string record);
	// Other Methods
	bool eof();
//	void enableDebug();
//	void disableDebug();
	std::vector<std::string> split(const std::string &s, char delim);
	void close();
	std::vector<std::string> arr;
private:
	void writeLabel(std::string label);
	void writeOperation(std::string operation);
	void writeOperand(std::string operand);
	void writeComment(std::string comment);
	std::string writeFiled(std::string str);
	void writeEnter();
	std::string writeAddress(std::string address);
	std::string trim(std::string input);
	std::vector<std::string> &split(const std::string &s, char delim,
			std::vector<std::string> &elems);
	std::ifstream in;
	std::ofstream out;
};

#endif /* FILEOPERATIONS_H_ */

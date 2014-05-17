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
//#include <string>
//using namespace std;

class FileOperations {
public:
	// Constructor/Destructor
	FileOperations(std::string fileName);
	~FileOperations();
	bool use(std::string filename);
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
	// Other Methods
	bool eof();
//	void enableDebug();
//	void disableDebug();
	void close();
private:
	void writeLabel(std::string label);
	void writeOperation(std::string operation);
	void writeOperand(std::string operand);
	void writeComment(std::string comment);
	void writeEnter();
	std::string writeAddress(std::string address);

	std::ifstream in;
	std::ofstream out;
};

#endif /* FILEOPERATIONS_H_ */

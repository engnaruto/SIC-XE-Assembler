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
//#include <string>
//using namespace std;

class FileOperations {
public:
	// Constructor/Destructor
	FileOperations();
	~FileOperations();
	//Reading Methods
	std::string readLine();
	std::string readLabel(std::string line);
	std::string readOperation(std::string line);
	std::string readOperand(std::string line);
	std::string readComment(std::string line);
	//Writing Methods
	void writeLine(std::string line);
	void writeLabel(std::string label);
	void writeOperation(std::string operation);
	void writeOperand(std::string operand);
	void writeComment(std::string comment);
	void writeEnter();
	// Other Methods
	bool eof();
	void enableDebug();
	void disableDebug();
	void close();
private:
	bool debug;
	std::ofstream file;
};

#endif /* FILEOPERATIONS_H_ */

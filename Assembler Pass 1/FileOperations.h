/*
 * FileOperations.h
 *
 *  Created on: May 12, 2014
 *      Author: Naruto
 */

#ifndef FILEOPERATIONS_H_
#define FILEOPERATIONS_H_

#include<iostream>

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
	void writeLabel();
	void writeOperation();
	void writeOperand();
	void writeComment();
	// Other Methods
	void enableDebug();
	void disableDebug();
	void close();
private:
	bool debug;
};

#endif /* FILEOPERATIONS_H_ */

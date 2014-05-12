/*
 * FileOperations.cpp
 *
 *  Created on: May 12, 2014
 *      Author: Naruto
 */

#include "FileOperations.h"
#include <fstream>
#include <iostream>
//#include<cstdio>
using namespace std;

FileOperations::FileOperations() {
	ofstream file("out.txt");
	debug = false;
}
FileOperations::~FileOperations() {

}

string FileOperations::readLine() {
	string s;
	getline(cin, s);
	return s;
}
string FileOperations::readLabel(string line) {

}
string FileOperations::readOperation(string line) {

}
string FileOperations::readOperand(string line) {

}
string FileOperations::readComment(string line) {

}
void FileOperations::writeLine(string line) {

//	file<<
}
void FileOperations::writeLabel() {

}
void FileOperations::writeOperation() {

}
void FileOperations::writeOperand() {

}
void FileOperations::writeComment() {

}
// Other Methods
void FileOperations::enableDebug() {

}
void FileOperations::disableDebug() {

}
void FileOperations::close() {

}


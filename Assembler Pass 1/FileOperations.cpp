/*
 * FileOperations.cpp
 *
 *  Created on: May 12, 2014
 *      Author: Naruto
 */

#include "FileOperations.h"
//#include<cstdio>
using namespace std;

FileOperations::FileOperations() {
	freopen("in.txt", "r", stdin);
	file.open("out.txt");
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
	return line.substr(0, 8);

}
string FileOperations::readOperation(string line) {
	return line.substr(10, 15);
}
string FileOperations::readOperand(string line) {
	return line.substr(18, 35);
}
string FileOperations::readComment(string line) {
	return line.substr(36, 66);
}
void FileOperations::writeLine(string line) {

	file << line << endl;
	if (debug) {
		cout << line << endl;
	}
}
void FileOperations::writeLabel(string label) {
	file << label;
	if (debug) {
		cout << label;
	}
	for (unsigned int i = 0; i < 9 - label.length(); i++) {
		file << " ";
		if (debug) {
			cout << " ";
		}
	}
}
void FileOperations::writeOperation(string operation) {
	file << operation;
	if (debug) {
		cout << operation;
	}
	for (unsigned int i = 0; i < 8 - operation.length(); i++) {
		file << " ";
		if (debug) {
			cout << " ";
		}
	}
}
void FileOperations::writeOperand(string operand) {
	file << operand;
	if (debug) {
		cout << operand;
	}
	for (unsigned int i = 0; i < 18 - operand.length(); i++) {
		file << " ";
		if (debug) {
			cout << " ";
		}
	}
}
void FileOperations::writeComment(string comment) {
	file << comment;
	if (debug) {
		cout << comment;
	}
}

void FileOperations::writeEnter() {
	file << "\n";
	if (debug) {
		cout << "\n";
	}
}
// Other Methods
void FileOperations::enableDebug() {
	debug = true;
}
void FileOperations::disableDebug() {
	debug = false;
}
void FileOperations::close() {
	file.close();
}


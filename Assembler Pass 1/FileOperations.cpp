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
}
FileOperations::~FileOperations() {

}

string FileOperations::readLine() {
	string s;
	getline(cin, s);
	return s;
}
string FileOperations::readLabel(string line) {
	return line.substr(0, 9);

}
string FileOperations::readOperation(string line) {
	return line.substr(10, 7);
}
string FileOperations::readOperand(string line) {
	return line.substr(18, 18);
}
string FileOperations::readComment(string line) {
	return line.substr(36, 31);
}
void FileOperations::writeLine(string line) {

	file << line << endl;
#ifdef debug
	cout << line << endl;
#endif
}

void FileOperations::writeLabel(string label) {
	file << label;
#ifdef debug
	cout << label;
#endif
	for (unsigned int i = 0; i < 9 - label.length(); i++) {
		file << " ";
#ifdef debug
		cout << " ";
#endif
	}
}
void FileOperations::writeOperation(string operation) {
	file << operation;
#ifdef debug
	cout << operation;
#endif
	for (unsigned int i = 0; i < 8 - operation.length(); i++) {
		file << " ";
#ifdef debug
		cout << " ";
#endif
	}
}
void FileOperations::writeOperand(string operand) {
	file << operand;
#ifdef debug
	cout << operand;
#endif
	for (unsigned int i = 0; i < 18 - operand.length(); i++) {
		file << " ";
#ifdef debug
		cout << " ";
#endif
	}
}
void FileOperations::writeComment(string comment) {
	file << comment;
#ifdef debug
	cout << comment;
#endif
}

void FileOperations::writeEnter() {
	file << "\n";
#ifdef debug
	cout << "\n";
#endif
}
// Other Methods
bool FileOperations::eof() {
	return file.eof();
}
void FileOperations::close() {
	file.close();
}


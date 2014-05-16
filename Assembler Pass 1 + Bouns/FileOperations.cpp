/*
 * FileOperations.cpp
 *
 *  Created on: May 12, 2014
 *      Author: Naruto
 */

#include "FileOperations.h"
//#include<cstdio>
using namespace std;

FileOperations::FileOperations(string fileName) {

	in.open("in.txt");
//	in.open(fileName.c_str());
	out.open("out.txt");
}
FileOperations::~FileOperations() {

}
void FileOperations::use(string fileName) {
//	in.open(fileName.c_str());
	in.open("in.txt");
	cout << "IN FILE" << endl;
//	freopen(fileName.c_str(), "r", stdin);
}

string FileOperations::readLine() {
	string s;
	arr.clear();
	arr.push_back("");
	arr.push_back("");
	arr.push_back("");
	arr.push_back("");
	getline(in, s);
	s = removeSpaces(s);
	splitBySpace(s);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	return s;
}

string FileOperations::removeSpaces(string line) {
	char output[66];
	int index = 0;
	for (unsigned int i = 0; i < line.length(); i++) {
		if (index != 0) {
			if ((line.at(i) == ',') && (output[index - 1] == ' ')) {
				output[index - 1] = ',';
				continue;
			}
			if ((output[index - 1] == ',') && (line.at(i) == ' ')) {
				continue;
			}
			if ((line.at(i) == ' ') && (output[index - 1] != ' ')) {
				output[index] = ' ';
				index++;
				continue;
			}
		}
		if ((index == 0) || (line.at(i) != ' ')
				|| ((line.at(i) == ' ') && (output[index - 1] != ' ')
						&& (output[index - 1] != ','))) {
			output[index] = line.at(i);
			index++;
			continue;
		}
	}
	string out = "";
	for (int i = 0; i < index; i++) {
		out += output[i];
	}
	if (out.at(0) == ' ') {
		out = out.substr(1);
	}
	return out;
}
void FileOperations::splitBySpace(string line) {
//	arr.reserve(4);
	int pos = line.find(" ");
	cout<<"************************"<<arr.size()<<endl;
	int index = 0;
	while (pos < 100 && pos > 0 && index < 4) {
		cout << pos << endl;
		if (index == 3)
			arr[index] = line;
		else {
			arr[index] = line.substr(0, pos);
			line = line.substr(pos + 1);
			pos = line.find(" ");
		}
		index++;
	}
}

string FileOperations::readLabel(string line) {
	return line.substr(0, 9);

}
string FileOperations::readOperation(string line) {
	return line.substr(9, 8);
}
string FileOperations::readOperand(string line) {
	return line.substr(17, 18);
}
string FileOperations::readComment(string line) {
	return line.substr(35, 31);
}

void FileOperations::writeFirst() {
//	cout<<"WRITEEEEEEEEEEEEEEEEEEEEEE"<<endl;

	out << "Line No.\tAddress\tLabel\tMnemonic\tOperand\tComments" << endl;
#ifdef debug
	cout << "Line No.\tAddress\t\tLabel\tMnemonic\tOperand\tComments" << endl;
#endif

}
void FileOperations::writeAll(int lineNo, string address, string label,
		string operation, string operand, string comment) {
	out << lineNo << "\t" << address << "\t" << label << "\t" << operation
			<< "\t" << operand << "\t" << comment << endl;
#ifdef debug
	cout << lineNo << "\t" << address << "\t" << label << "\t" << operation
			<< "\t" << operand << "\t" << comment << endl;
#endif

}

void FileOperations::writeLine(string line) {

	out << line << endl;
#ifdef debug
	cout << line << endl;
#endif
}

void FileOperations::writeLabel(string label) {
	out << label;
#ifdef debug
	cout << label;
#endif
	for (unsigned int i = 0; i < 9 - label.length(); i++) {
		out << " ";
#ifdef debug
		cout << " ";
#endif
	}
}
void FileOperations::writeOperation(string operation) {
	out << operation;
#ifdef debug
	cout << operation;
#endif
	for (unsigned int i = 0; i < 8 - operation.length(); i++) {
		out << " ";
#ifdef debug
		cout << " ";
#endif
	}
}
void FileOperations::writeOperand(string operand) {
	out << operand;
#ifdef debug
	cout << operand;
#endif
	for (unsigned int i = 0; i < 18 - operand.length(); i++) {
		out << " ";
#ifdef debug
		cout << " ";
#endif
	}
}
void FileOperations::writeComment(string comment) {
	out << comment;
#ifdef debug
	cout << comment;
#endif
}

void FileOperations::writeEnter() {
	out << "\n";
#ifdef debug
	cout << "\n";
#endif
}
// Other Methods
bool FileOperations::eof() {
	return in.eof();
}
void FileOperations::close() {
	in.close();
	out.close();
}


/*
 * FileOperations.cpp
 *
 *  Created on: May 12, 2014
 *      Author: Naruto
 */

#include "FileOperations.h"
#include <stdio.h>
#include <string.h>


//#include<cstdio>
using namespace std;

FileOperations::FileOperations(string fileName) {
//	in.open("in.txt");
	in.open(fileName.c_str());
	out.open("out.txt");
}
FileOperations::~FileOperations() {

}
bool FileOperations::use(string fileName) {
//	in.clear();
	in.close();
	in.open(fileName.c_str());
//	if (in) {
//		return true;
//	}
//	return false;
	return in.good();
//	in.open("in.txt");
//	cout << "IN FILE" << endl;
//	freopen(fileName.c_str(), "r", stdin);
}

string FileOperations::readLine() {
	string s;
	getline(in, s);
	return s;
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
	if (out.length()>0&&out.at(0) == ' ') {
		out = out.substr(1);
	}
	return out;
}

vector<string> FileOperations::split(string str, std::string sep) {
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<std::string> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

void FileOperations::writeFirst() {
//	cout<<"WRITEEEEEEEEEEEEEEEEEEEEEE"<<endl;
	out << "Line No.\t\tAddress\t\t    Label\t\t    Mnemonic\t\tOperand\t\tComments"
			<< endl;
#ifdef debug
	cout << "Line No.\t\tAddress\t\t\t     Label\t\t    Mnemonic\t\tOperand\t\tComments"
			<< endl;
#endif

}
string FileOperations::writeFiled(string str) {

	for (unsigned int i = 0; i < 15 - str.length(); i++) {
		str += " ";
	}
	return str;
}
void FileOperations::writeAll(int lineNo, string address, string label,
		string operation, string operand, string comment) {
	ostringstream convert;   // stream used for the conversion
	convert << lineNo; // insert the textual representation of 'Number' in the characters in the stream
	string s = convert.str();
	s = writeFiled(s);
	address = writeFiled(address);
	label = writeFiled(label);
	operation = writeFiled(operation);
	operand = writeFiled(operand);
	out << s << "\t\t" << address << "\t\t" << label << "\t\t" << operation
			<< "\t\t" << operand << "\t\t" << comment << endl;
#ifdef debug
	cout << s << "\t\t" << address << "\t\t" << label << "\t\t" << operation
			<< "\t\t" << operand << "\t\t" << comment << endl;
#endif

}
//void FileOperations::writeAll(int lineNo, string address, string label,
//		string operation, string operand, string comment) {
//	out << lineNo << "\t" << address << "\t" << label << "\t" << operation
//			<< "\t" << operand << "\t" << comment << endl;
//#ifdef debug
//	cout << lineNo << "\t" << address << "\t" << label << "\t" << operation
//			<< "\t" << operand << "\t" << comment << endl;
//#endif
//
//}

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
//string FileOperations::writeAddress(std::string address) {
//	string s = "";
//	for (unsigned int i = 0; i < 5 - address.length(); i++) {
//		s += "0";
//	}
//	s += address;
////	cout<<"DDDDDDDDDDDD "<<s<<endl;
//	return address;
//}
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


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

bool FileOperations::writeIn(std::string filename) {
	out.close();
	out.open(filename.c_str());
	return out.good();
}
string FileOperations::readLabel(string line) {
	return line.substr(0, 8);

}
string FileOperations::readOperation(string line) {
	return line.substr(8, 9);
}
string FileOperations::readOperand(string line) {
	return line.substr(17, 18);
}
string FileOperations::readComment(string line) {
	return line.substr(35, 31);
}

void FileOperations::writeFirst() {
//	cout<<"WRITEEEEEEEEEEEEEEEEEEEEEE"<<endl;
	out
			<< "Line No.\t\tAddress\t\t    Label\t\t    Mnemonic\t\tOperand\t\tComments"
			<< endl;
#ifdef debug
	cout
			<< "Line No.\t\tAddress\t\t\t     Label\t\t    Mnemonic\t\tOperand\t\tComments"
			<< endl;
#endif

}
string FileOperations::writeFiled(string str) {
	if (str.length() <= 15) {
		for (unsigned int i = 0; i < 15 - str.length(); i++) {
			str += " ";
		}
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
//	cout << "*******************" << endl;
	out << s << "\t\t" << address << "\t\t" << label << "\t\t" << operation
			<< "\t\t" << operand << "\t\t" << comment << endl;
#ifdef debug
	cout << s << "\t\t" << address << "\t\t" << label << "\t\t" << operation
			<< "\t\t" << operand << "\t\t" << comment << endl;
#endif

}
void FileOperations::writeAll(string address, string objectCode, string label,
		string operation, string operand) {
	objectCode = writeFiled(objectCode);
	address = writeFiled(address);
	label = writeFiled(label);
	operation = writeFiled(operation);
	operand = writeFiled(operand);
//	cout << "*******************" << endl;
	out << address << " " << objectCode << " " << label << " " << operation
			<< " " << operand << endl;
#ifdef debug
//	out << address << " " << objectCode << " " << label << " " << operation
//			<< " " << operand << endl;
#endif

}
void FileOperations::writeImmidiate(string address, string label,
		string operation, string operand) {

//	address = writeFiled(address);
//	label = writeFiled(label);
//	operation = writeFiled(operation);
//	operand = writeFiled(operand);
	if (trim(address).size() == 0) {
		address = "-";
	}
	if (trim(label).size() == 0) {
		label = "-";
	}
	if (trim(operation).size() == 0) {
		operation = "-";
	}
	if (trim(operand).size() == 0) {
		operand = "-";
	}
//	cout << "*******************" << endl;
	out << address << " " << label << " " << operation << " " << operand
			<< endl;
#ifdef debug
//	cout << address << " " << label << " " << operation << " " << operand
//			<< endl;
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
void FileOperations::writeTxtRecord(string strtAddress, string length,
		string record) {
	out << "T" << strtAddress << "^" << length << "^" << record << endl;
#ifdef debug
//	cout << "T" << strtAddress << "^" << length << "^" << record << endl;
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

string FileOperations::trim(string input) {
	string output = "";

	for (unsigned int i = 0; i < input.length(); i++) {
		if (input[i] != ' ' && input[i] != '\t') {
			output = output + input[i];
		}
	}
	return output;
}
vector<string> &FileOperations::split(const string &s, char delim,
		vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> FileOperations::split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}


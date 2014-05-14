/*
 * pass1.cpp
 *
 *  Created on: May 14, 2014
 *      Author: Naruto
 */

#include "pass1.h"

using namespace std;

//map<string, OpInfo> opTable;
//map<string, string> symTable;

vector<string> &pass1::split(const string &s, char delim,
		vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> pass1::split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

void pass1::loadHash() {
	fstream file;
	file.open("hashTable.txt");
	while (!file.eof()) {
		string s;
		getline(file, s);
		vector<string> arr = split(s, ' ');
		OpInfo o(arr[1], arr[2], arr[3]);
		opTable.insert(pair<string, OpInfo>(arr[0], o));
	}

	file.close();
	for (map<string, OpInfo>::iterator it = opTable.begin();
			it != opTable.end(); ++it) {
		cout << it->first << " => " << it->second.format << " => "
				<< it->second.opcode << " => " << it->second.operand << '\n';
	}

}

//bool checkOperandOperation(string operand, string operation) {
//	string mapOperand = OpTable[operation].operand;
//	if (operand.compare("-") == 0) {
//		if (operand.length() == 0) {
//			return true;
//		}
//	} else if (operand.compare("r1,r2") == 0) {
//		if (condition) {
//
//		}
//	} else if (operand.compare("r1") == 0) {
//		if (condition) {
//
//		}
//	} else {
//
//	}
//}

int pass1::main(int argc, char **argv) {
	loadHash();
	FileOperations file;

	while (!file.eof()) {
		try {

			string line = file.readLine();
			string label = file.readLabel(line);
			string operand = file.readOperand(line);
			string operation = file.readOperation(line);
			string comment = file.readComment(line);
			//check all

			//check operandOperation
//		checkOperandOperation(operand, operation);
		} catch (exception & e) {
			file.writeLine("**error occurred in the previous line");
		}
	}

//	file.enableDebug();
//	file.writeLine("hiiiiiiiiiiiii");
//	string s = file.readLine();
//	file.writeLine(s);
	file.close();
	return 0;
}

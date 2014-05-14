/*
 * pass1.cpp
 *
 *  Created on: May 14, 2014
 *      Author: Naruto
 */

#include "Tables.h"

using namespace std;

//map<string, OpInfo> opTable;
//map<string, string> symTable;
Tables::Tables() {

}
Tables::~Tables() {

}

vector<string> &Tables::split(const string &s, char delim,
		vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> Tables::split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

void Tables::loadHash() {
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
#ifdef debug
//	cout << "hiiiiiiiiiii"<<endl;

	for (map<string, OpInfo>::iterator it = opTable.begin();
			it != opTable.end(); ++it) {
		cout << it->first << " => " << it->second.format << " => "
		<< it->second.opcode << " => " << it->second.operand << '\n';
	}
#endif

	cout << "";

}

string Tables::toLowerCase(string input) {
	unsigned int i;
	string tmp = "";
	for (i = 0; i < input.length(); i++) {
		char c = input[i];
		int n = tolower(c);
		char d = char(n);
		tmp = tmp + d;
	}
	return tmp;
}
int Tables::getLength(string operation, string operand) {
	if (operation == "word") {
		return 3;
	} else if (operation == "byte") {
		if (operand.at(0) == 'x')
			return 1;
		else if (operand.at(0) == 'c') {
			int len = operand.length() - 3;
			return len;
		}

	} else if (operation == "resw") {
		int counter = atoi(operand.c_str()) * 3;
		return counter;
	} else if (operation == "resb") {
		int counter = atoi(operand.c_str());
		return counter;
	} else {
		if (operation.at(0) == '+')
			return 4;
		else {
			string s = ""; //opTable[operation].format;
			if (s.at(0) == '1')
				return 1;
			else if (s.at(0) == '2')
				return 2;
			else
				return 3;
		}
	}
	return 0;
}


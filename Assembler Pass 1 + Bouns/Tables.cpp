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

//	for (map<string, OpInfo>::iterator it = opTable.begin();
//			it != opTable.end(); ++it) {
//		cout << it->first << " => " << it->second.format << " => "
//		<< it->second.opcode << " => " << it->second.operand << '\n';
//	}
#endif

//	cout << "";

}

int Tables::getLength(string operation, string operand) {
//			cout << "--------HEREEEEEEEEEEE " << operation <<"   "<<operand<< endl;
	string x = toLowerCase(operation);
	string s = toLowerCase(operand);
	if (x == "start" || x == "end") {
		return 0;
	} else if (x == "byte") {
		if (s.at(0) == 'x') {
			int len = s.length() - 3;
//			cout<<"length "<<len/2<<endl;
			return len / 2;
		} else if (s.at(0) == 'c') {
			int len = s.length() - 3;
			return len;
		}

	} else if (x == "resw") {
		int counter = atoi(s.c_str()) * 3;
		return counter;
	} else if (x == "resb") {
		int counter = atoi(s.c_str());
		return counter;
	} else if (x == "word") {
		return 3;
	} else {
		if (x.at(0) == '+')
			return 4;
		else {
			string s = toLowerCase(x);
			string c = opTable[s].format;
			if (c.at(0) == '1')
				return 1;
			else if (c.at(0) == '2')
				return 2;
			else
				return 3;
		}
	}
	return 0;
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

string Tables::printSymTable() {
	string s;

	s += "\n\n******************************************\n";
	s += "*             Symbol Table               *\n";
	s += "******************************************\n";
//cout<<"%%%%%%%%%%   "<< symTable.size()<<endl;
	string z = "";
	string x = "";
	for (map<string, string>::iterator it = symTable.begin();
			it != symTable.end(); ++it) {
		z = it->first;
		x = it->second;

		for (unsigned int i = 0; i < 20 - x.size(); i++) {
			x  +=" ";
		}
		for (unsigned  int i = 0; i < 20 - z.size(); i++) {
			z += " ";
		}
//		cout << "*\t" + z + "*" + x + "\t*\n";
		s += "*     " + z + "\t*     \t" + x + "*\n";
	}
	s += "******************************************\n";
	return s;
}

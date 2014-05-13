#include <iostream>
#include <map>
#include <vector>
#include <sstream>
//#include <stdio.h>
#include "FileOperations.h"
#include "OpInfo.h"
using namespace std;

map<string, OpInfo> OpTable;
map<string, string> symTable;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}


void loadHash(){

}

bool checkHashTabeles(string label) {
	OpInfo o = OpTable[label];
	string s = symTable[label];
//	if (o == nullptr && s == nullptr) {
//
//	}
}

int main(int argc, char **argv) {
	FileOperations file;
	file.enableDebug();
	file.writeLine("hiiiiiiiiiiiii");
	string s = file.readLine();
	file.writeLine(s);
	file.close();

}

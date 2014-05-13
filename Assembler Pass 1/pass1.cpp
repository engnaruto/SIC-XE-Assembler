#include <iostream>
#include <map>
#include "FileOperations.h"
#include "OpInfo.h"
using namespace std;

map<string, OpInfo> OpTable ;
map<string, string> symTable;

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

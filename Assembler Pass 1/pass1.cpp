#include <iostream>
#include<stdio.h>
#include<cstdio>
#include <fstream>
#include "FileOperations.h"
#include <h>
using namespace std;

int main(int argc, char **argv) {
	FileOperations file;
	file.enableDebug();
	file.writeLine("hiiiiiiiiiiiii");
	string s = file.readLine();
	file.writeLine(s);
	file.close();


}

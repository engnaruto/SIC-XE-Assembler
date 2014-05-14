#include "Tables.h"
#include "debug.cpp"
using namespace std;

int main(int argc, char **argv) {
#ifdef debug
	cout << "hiiiiiiiiiii" << endl;
#endif

	Tables tables;
	tables.loadHash();
//	FileOperations file;
//
//	while (!file.eof()) {
//		try {
//
//			string line = file.readLine();
//			string label = file.readLabel(line);
//			string operand = file.readOperand(line);
//			string operation = file.readOperation(line);
//			string comment = file.readComment(line);
//			//check all
//
//			//check operandOperation
////		checkOperandOperation(operand, operation);
//		} catch (exception & e) {
//			file.writeLine("**error occurred in the previous line");
//		}
//	}
//
////	file.enableDebug();
////	file.writeLine("hiiiiiiiiiiiii");
////	string s = file.readLine();
////	file.writeLine(s);
//	file.close();
	return 0;
}

#include <vector>
#include "Tables.h"
#include "debug.cpp"
#include "check.h"
#include "LocCounter.h"

using namespace std;

string line, label, operand, operation, comment, lowerCaseLine;
int length;
void readSplitLine(FileOperations &file) {
	line = file.readLine();
	if (line[0] != '.') {
		if (line.size() < 15) {
			throw;
		} else if (line.size() > 35) {
			label = file.readLabel(line);
			operand = file.readOperand(line);
			operation = file.readOperation(line);
			comment = file.readComment(line);

		} else if (line.size() > 15) {
			label = file.readLabel(line);
			operand = file.readOperand(line);
			operation = file.readOperation(line);
			comment = "";
		} else {
			label = file.readLabel(line);
			operand = file.readOperand(line);
			operation = "";
			comment = "";
		}
	}
}

string trim(string input) {
	string output = "";

	for (unsigned int i = 0; i < input.length(); i++) {
		if (input[i] != ' ' && input[i] != '\t') {
			output = output + input[i];
		}
	}
	return output;
}

int main(int argc, char **argv) {
	Tables tables;
	FileOperations file("in.txt");
	LocCounter counter(0);
	try {
		tables.loadHash();
	} catch (exception &e) {
		file.writeLine("Error: Can't load hashTable.txt");
	}

//	string c;
//	vector<string> v;
//	while (1) {
//		cout << "Enter: pass1 <source-file-name>" << endl;
//		getline(cin, c);
//		v = tables.split(c, ' ');
//		if (v[0] == "pass1") {
//			try {
//		cout << v[0] << " " << v[1] << endl;
//				file.use(v[1]);
//				break;
//			} catch (exception &e) {
//				continue;
//			}
//		}
//	}

	Check check(tables);
	try {
		readSplitLine(file);
	} catch (exception& e) {
		file.writeLine("Error: Line is too short !!!");
	}

				cout << "hiiiiiiiiiiiiiiiii" << endl;
	string s = check.checkAll(label, operand, operation);
	if (s.length() != 0) {
		file.writeLine(s);
		s = "";
	}
	file.writeFirst();
	string t = trim(operand);
	if (t == "start") {
		counter.setCounter(operation);
		file.writeAll(counter.getLineCounter(), counter.getAddress(), label,
				operation, operand, comment);

	} else {
		counter.setCounter(0);
		length = tables.getLength(operand, operation);
		counter.AddtoCounter(length);
		file.writeAll(counter.getLineCounter(), counter.getAddress(), label,
				operation, operand, comment);
	}

	while (!file.eof()) {
		try {

			try {
				readSplitLine(file);
			} catch (exception& e) {
				file.writeLine("Error: Line is too short !!!");
			}

			string s = check.checkAll(label, operand, operation);
			length = tables.getLength(operand, operation);
			counter.AddtoCounter(length);
			file.writeAll(counter.getLineCounter(), counter.getAddress(), label,
					operation, operand, comment);
			if (s.length() != 0) {
				file.writeLine(s);
				s = "";
			}
		} catch (exception & e) {
			file.writeLine("**error occurred in the previous line");
		}
	}

	t = trim(operand);
	if (t != "end") {
		file.writeLine("Error: No End Mnemonic");
	}

	file.close();
	return 0;
}

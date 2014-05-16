#include <vector>
#include "Tables.h"
#include "debug.cpp"
#include "Check.h"
#include "LocCounter.h"

using namespace std;

string line, label, operand, operation, comment, lowerCaseLine, strexc, t;
int length;
bool ok;
string readSplitLine(FileOperations &file) {
	line = file.readLine();

	string s = "";
	if (line[0] != '.') {
		if (line.size() < 12) {
//			throw;
			s = "\t***Error: Line is too short !!!\n";
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
			operation = file.readOperation(line);
			operand = "";
			comment = "";
		}
	} else {
		s = "Comment";
	}
	return s;
}

int main(int argc, char **argv) {
	Tables tables;
	FileOperations file("in.txt");
	LocCounter counter(0);
	ok = true;
	try {
		tables.loadHash();
	} catch (exception &e) {
		file.writeLine("Error: Can't load hashTable.txt");
		ok = false;
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

	file.writeFirst();
	Check check(tables);
	strexc = "";
	while (!file.eof()) {
		strexc = readSplitLine(file);

		if (strexc.size() == 0) {

			strexc = check.checkAll(&label, &operation, &operand);
			if (strexc.length() != 0) {
				file.writeAll(counter.getLineCounter(), counter.getAddress(),
						label, operation, operand, comment);
				file.writeLine(strexc);
				strexc = "";
				ok = false;
				continue;
			}
			t = check.toLowerCase(operation);
			if (t == "start") {
				counter.setCounter(operand);
			} else {
				counter.setCounter("0");
			}
			length = tables.getLength(operation, operand);
			counter.addtoCounter(length);
			file.writeAll(counter.getLineCounter(), counter.getAddress(), label,
					operation, operand, comment);

			break;
		} else {
			if (strexc == "Comment") {
				file.writeLine(line);
			} else {
				file.writeLine(strexc);
				ok = false;
			}
		}
	}
	while (!file.eof()) {

		strexc = readSplitLine(file);
		if (strexc.size() == 0) {
			strexc = check.checkAll(&label, &operation, &operand);
//			string s = check.checkAll(label, operand, operation);
			if (strexc.length() != 0) {
				file.writeAll(counter.getLineCounter(), counter.getAddress(),
						label, operation, operand, comment);
				file.writeLine(strexc);
//				strexc = "";
				ok = false;
				continue;
			}
			length = tables.getLength(operation, operand);
			counter.addtoCounter(length);
			file.writeAll(counter.getLineCounter(), counter.getAddress(), label,
					operation, operand, comment);
			if (strexc.length() != 0) {
//				cout<<"INNNNNNNNNN"<<endl;
				file.writeLine(strexc);
				strexc = "";
				ok = false;
			}
		} else {
			if (strexc == "Comment") {
				file.writeLine(line);
			} else {
				file.writeLine(strexc);
				ok = false;
			}
		}

	}
	t = check.toLowerCase(operation);
	if (t != "end") {
//		cout<<"^^^^^^^^^^^^^  "<<t<<endl;
		file.writeLine("\t***Error: No End Mnemonic\n");
	}

	if (ok) {
		file.writeLine("\n>>    S U C C E S S F U L    A S S E M B L Y");
	} else {
		file.writeLine("\n>>    I N C O M P L E T E    A S S E M b L Y");
	}

	file.close();
	return 0;
}

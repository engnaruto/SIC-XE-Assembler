#include <vector>
#include "FileOperations.h"
#include "Tables.h"
#include "Check.h"
#include "debug.cpp"
#include "LocCounter.h"

using namespace std;

string line, label, operand, operation, comment, lowerCaseLine, strexc, t;
int length;
string readSplitLine(FileOperations &file) {
	line = file.readLine();

	string s = "";
	if (line[0] != '.') {
		if (line.size() < 12) {
//			throw;
			s = "Error: Line is too short !!!\n";
		}
//		else if (line.size() > 35) {
//			label = file.readLabel(line);
//			operand = file.readOperand(line);
//			operation = file.readOperation(line);
//			comment = file.readComment(line);
//
//		} else if (line.size() > 15) {
//			label = file.readLabel(line);
//			operand = file.readOperand(line);
//			operation = file.readOperation(line);
//			comment = "";
//		} else {
//			label = file.readLabel(line);
//			operation = file.readOperation(line);
//			operand = "";
//			comment = "";
//		}
//	} else {
//		s = "Comment";
	}
		return s;
	}

int main(int argc, char **argv) {
	Tables tables;
	LocCounter counter(0);
	Check check(tables);
	FileOperations file("in.txt");
	try {
		tables.loadHash();
	} catch (exception &e) {
		file.writeLine("Error: Can't load hashTable.txt");
		return 0;
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
	strexc = "";
	while (!file.eof()) {
		strexc = readSplitLine(file);
		if (strexc.size() == 0) {

			strexc = check.checkAll(file.arr,&label, &operation, &operand,&comment);
//			if (strexc.length() != 0) {
//				file.writeAll(counter.getLineCounter(), counter.getAddress(),
//						label, operation, operand, comment);
//				file.writeLine(strexc);
//				strexc = "";
//				continue;
//			}
			t = check.toLowerCase(operation);
			if (t == "start") {
cout<<"-------------------------"<<endl;
				counter.setCounter(operand);
				file.writeAll(counter.getLineCounter(), counter.getAddress(),
						label, operation, operand, comment);

			} else {
				counter.setCounter(0);
				length = tables.getLength(operand, operation);
				counter.addtoCounter(length);
				file.writeAll(counter.getLineCounter(), counter.getAddress(),
						label, operation, operand, comment);
			}
			break;
		} else {
			if (strexc == "Comment") {
				file.writeLine(line);
			} else {
				file.writeLine(strexc);
			}
		}
	}

	while (!file.eof()) {

		strexc = readSplitLine(file);
		if (strexc.size() == 0) {
			strexc = check.checkAll(file.arr,&label, &operation, &operand,&comment);
//			string s = check.checkAll(label, operand, operation);
			length = tables.getLength(operation, operand);
			counter.addtoCounter(length);
			file.writeAll(counter.getLineCounter(), counter.getAddress(), label,
					operation, operand, comment);
			if (strexc.length() != 0) {
				file.writeLine(strexc);
				strexc = "";
			}
		} else {
			if (strexc == "Comment") {
				file.writeLine(line);
			} else {
				file.writeLine(strexc);
			}
		}

	}
	t = check.toLowerCase(operation);
	if (t != "end") {
		file.writeLine("Error: No End Mnemonic");
	}

	file.close();
	return 0;
}

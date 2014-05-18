#include <vector>
#include "Tables.h"
#include "debug.cpp"
#include "Check.h"
#include "LocCounter.h"

using namespace std;
#include <vector>

string line, label, operand, operation, comment, strexc, t, progname;
int length;
bool ok;
bool end;
bool checkOperation(string *operation, Check &check, Tables &tables) {
	string x = check.toLowerCase(*operation);
	string dir[6];
	dir[0] = "word";
	dir[1] = "byte";
	dir[2] = "resb";
	dir[3] = "resw";
	dir[4] = "start";
	dir[5] = "end";
	if (x[0] == '+') {
		string tmp = "";
		tmp.assign(x.begin() + 1, x.end());
		x.assign(tmp);
	}
	int found = tables.opTable.count(x);
	if (found > 0) {
		return true;
	}
	int i;
	for (i = 0; i < 6; i++) {
		if (x == dir[i]) {
			return true;
		}
	}

	return false;
}
void split(vector<string> arr, Check &check, Tables &tables) {
	string tmp = arr[0];
	if (tmp[0] == '.') {
		for (unsigned int i = 0; i < arr.size(); i++) {
			comment = comment + arr[i];
		}
	} else {
		bool ch = checkOperation(&arr[0], check, tables);
		if (ch) {
			operation = arr[0];
			if (arr.size() > 1)
				operand = arr[1];
		} else {
			label = arr[0];
			if (arr.size() > 1)
				operation = arr[1];
			if (arr.size() > 2)
				operand = arr[2];
		}
	}
}

string readSplitLine2(FileOperations &file, Check &check, Tables &tables) {
	label = "";
	operation = "";
	operand = "";
	comment = "";
	string s = "";
	line = file.readLine();
	string st = file.removeSpaces(line);
	vector<string> arr = file.split(st, " ");
	if (arr.size() > 0) {
		if (arr[0].at(0) == '.') {
			s = "Comment";
			return s;
		} else {
			split(arr, check, tables);
			return "";
		}
	} else
		return "Comment";
	return "";
}

string readSplitLine(FileOperations &file) {

	line = file.readLine();

	if ((operation == "END" || operation == "end") && line.size() == 0) {
		return "";
	}
	string s = "";
	if (line[0] != '.') {
		cout << "sizeee   " << line.size() << endl;
		if (line.size() < 11) {
//			throw;

			s = "\t***Error: Line is too short !!!\n";
		} else if (line.size() > 35) {
			label = file.readLabel(line);
			operand = file.readOperand(line);
			operation = file.readOperation(line);
			comment = file.readComment(line);

		} else if (line.size() > 16) {
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

void openFile(Tables& tables, FileOperations& file) {
	string c;
	vector<string> v;
	while (1) {
		cout << "Enter: pass1 <source-file-name>" << endl;
		getline(cin, c);
		v.clear();
		v = tables.split(c, ' ');
		//		cout << v[0] << " " << v[1] << endl;
		//		cout << file.use(v[1]) << endl;
		if (v.size() > 1 && v[0] == "pass1" && file.use(v[1])) {
			//			file.use(v[1]);
			break;
		} else {
			cout << "***Error: Invalid filename" << endl;
		}
	}
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

	//openFile(tables, file);
	file.writeFirst();
	Check check(&tables);
	strexc = "";
	int i = 0;

	while (!file.eof()) {
		cout << "hi2 " << i++ << endl;

		strexc = readSplitLine2(file, check, tables);

		if (strexc.size() == 0) {

			strexc = check.checkAll(counter.getAddressLabel(), &label,
					&operation, &operand);
			if (strexc.length() != 0) {
				counter.addtoCounter(3);
				file.writeAll(counter.getLineCounter(), counter.getAddress(),
						label, operation, operand, comment);
				file.writeLine(strexc);
				strexc = "";
				ok = false;
				continue;
			}
			t = check.toLowerCase(operation);
			if (t == "start") {
				progname = label;
				counter.setCounter(operand);
			} else {
				progname = "";
				counter.setCounter("0");
			}
			length = tables.getLength(operation, operand);
			counter.addtoCounter(length);
			t = check.toLowerCase(label);
			if (!check.trim(t).empty()) {
				tables.symTable[t] = counter.getAddressLabel();
			}
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
		cout << "hi " << i++ << endl;
		strexc = readSplitLine2(file, check, tables);
		if (strexc.size() == 0) {
			strexc = check.checkAll(counter.getAddressLabel(), &label,
					&operation, &operand);
			if (strexc.length() != 0) {
				counter.addtoCounter(3);
				file.writeAll(counter.getLineCounter(), counter.getAddress(),
						label, operation, operand, comment);
				file.writeLine(strexc);
				ok = false;
				continue;
			}
			length = tables.getLength(operation, operand);
			counter.addtoCounter(length);
			t = check.toLowerCase(label);
			if (!check.trim(t).empty()) {
				tables.symTable[t] = counter.getAddressLabel();
			}
			file.writeAll(counter.getLineCounter(), counter.getAddress(), label,
					operation, operand, comment);
			if (strexc.length() != 0) {
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
		t = check.toLowerCase(operation);
		if (t == "end")
			end = true;
	}
	t = check.toLowerCase(operation);
	cout << "op  " << operation << endl;
	if (end == false) {
//		cout<<"^^^^^^^^^^^^^  "<<t<<endl;
		file.writeLine("\t***Error: No End Mnemonic\n");
		ok = false;
	} else {
		if (progname != operand && !operand.empty()) {
			file.writeLine("\t***Error: Invalid relocatable address \n");
			ok = false;
		}
	}

	if (ok) {
		file.writeLine("\n>>    S U C C E S S F U L    A S S E M B L Y");
	} else {
		file.writeLine("\n>>    I N C O M P L E T E    A S S E M b L Y");
	}

	file.writeLine(tables.printSymTable());
	file.close();
	return 0;
}

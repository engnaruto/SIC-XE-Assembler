#include <vector>
#include "Tables.h"
#include "debug.cpp"
#include "Check.h"
#include "LocCounter.h"

using namespace std;

string line = "", address = "", label = "", operand = "", operation = "",
		progname = "", comment = "", strexc = "", proglength = "", t = "",
		txtRec = "", startaddress = "", recAddress = "";
int length = 0;
bool ok = true, tooShort = false;
vector<string> arr;
vector<string> format4;
string readSplitLine(FileOperations &file) {
	line = file.readLine();
	string s = "";
	if (line[0] != '.') {
		if (line.size() < 12) {
//			throw;
			tooShort = true;
//			s = "\t***Error: Line is too short !!!\n";
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
string readImmidiate(FileOperations &file) {
	line = file.readLine();
	string s = "";
	if (line[0] == '.') {
		s = "Comment";
	} else {
		arr.clear();
		arr = file.split(line, ' ');
		address = arr[0];
		label = arr[1];
		if (label == "-") {
			label = "";
		}
		operation = arr[2];
		operand = arr[3];
		if (operand == "-") {
			operand = "";
		} else if (arr.size() > 4) {
			for (unsigned int i = 5; i < arr.size(); i++) {
				operand += " " + arr[i];
			}
		}
//		cout <<"**************** "<< arr[0]<<"   "<< arr[1]<<"   "<< arr[2]<<"   "<< arr[3]<<"   " << endl;
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
	FileOperations imFile("i.txt");
	imFile.writeIn("immidiate.txt");
	LocCounter counter("0");
	tooShort = false;
	ok = true;
	try {
		tables.loadHash();
	} catch (exception &e) {
		file.writeLine("Error: Can't load hashTable.txt");
		ok = false;
	}

//	openFile(tables, file);

	file.writeFirst();
	Check check(&tables);
	strexc = "";
	while (!file.eof()) {

		if (tooShort) {
			tooShort = false;
			file.writeLine("\t***Error: Line is too short !!!\n");
		}

		strexc = readSplitLine(file);

		if (strexc.size() == 0) {

			strexc = check.checkAll(counter.getAddressLabel(), &label,
					&operation, &operand, &counter);

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
//				progname = label;
//				progname = "";
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
			imFile.writeImmidiate(counter.getAddressLabel(), label, operation,
					operand);

			break;
		} else {
			if (strexc == "Comment") {
				file.writeLine(line);
				imFile.writeLine(line);
			} else {
				file.writeLine(strexc);
				ok = false;
			}
		}
	}
	while (!file.eof()) {
		if (tooShort) {
			tooShort = false;
			file.writeLine("\t***Error: Line is too short !!!\n");
		}
		label = operand = operation = "";
		strexc = readSplitLine(file);
		if (check.trim(line).size() == 0) {
			strexc += "\t***Error: Line is too short !!!\n";
		}
		if (strexc.size() == 0) {
			strexc = check.checkAll(counter.getAddressLabel(), &label,
					&operation, &operand, &counter);
//			cout << strexc << endl;
			if (strexc.length() != 0) {
				counter.addtoCounter(3);
				file.writeAll(counter.getLineCounter(), counter.getAddress(),
						label, operation, operand, comment);
				file.writeLine(strexc);
				ok = false;
				continue;
			}
			string x = tables.toLowerCase(operation);
			if (x == "equ" || x == "org") {
				file.writeAll(counter.getLineCounter(), "", label, operation,
						operand, comment);
				imFile.writeImmidiate("", label, operation, operand);
			} else {
				length = tables.getLength(operation, operand);
				counter.addtoCounter(length);
				t = check.toLowerCase(label);
				if (!check.trim(t).empty()) {
					tables.symTable[t] = counter.getAddressLabel();
				}
				file.writeAll(counter.getLineCounter(), counter.getAddress(),
						label, operation, operand, comment);
				imFile.writeImmidiate(counter.getAddressLabel(), label,
						operation, operand);
			}
			if (strexc.length() != 0) {
				file.writeLine(strexc);
				strexc = "";
				ok = false;
			}
		} else {
			if (strexc == "Comment") {
				file.writeLine(line);
				imFile.writeLine(line);
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
		ok = false;
	} else {
//		operand = check.trim(operand);
//		cout << "%%%%%%%   " << operand << "    " << progname << endl;
		int x = tables.symTable.count(operand);
		if (x > 0 && !operand.empty()) {
			file.writeLine("\t***Error: Invalid relocatable address \n");
			ok = false;
		}
	}

	if (ok) {
		file.writeLine("\n>>    S U C C E S S F U L    A S S E M B L Y\n");
		file.writeLine("\n\n>>    S T A R T I N G  P A S S  2");
		proglength = counter.getAddressLabel();
	} else {
		file.writeLine("\n>>    I N C O M P L E T E    A S S E M b L Y");
	}

	file.writeLine(tables.printSymTable());
	imFile.close();
	if (ok) {
		file.use("immidiate.txt");
		imFile.writeIn("OPFILE.txt");
		while (!file.eof()) {
			strexc = readImmidiate(file);
			if (strexc == "Comment") {
				file.writeLine(line);
			} else {
				string x = check.toLowerCase(operation);
//				cout << "&&&&&&&&&&&&&&   " << x << endl;
				if (x == "start") {
					if (progname.size() < 6) {
						for (unsigned int i = 0; i < 6 - progname.length();
								i++) {
							progname += " ";
						}
					}
					imFile.writeLine(
							"H" + progname + "^" + address + "^" + proglength);
				} else {
					if (operation[0] == '+') {
//						cout << "~~~~~~~~~~~~  " << address << endl;
						format4.push_back(address);
					}
					int length = tables.getLength(operation, operand);
					int curAddress = counter.conHexaToDec(address);
					length += curAddress;
					string nextAddress = counter.dectoHex(length);
					string objectCode = check.format(operation, operand,
							nextAddress);		//call ebtehal
					if (objectCode == "") {
						file.writeAll(address, "", label, operation, operand);
						file.writeLine("\t***Error: Invalid Label\n");
						ok = false;
					} else if (objectCode == "dir") {
						string length = counter.dectoHex(txtRec.size());
						if (txtRec != "") {
							imFile.writeTxtRecord(recAddress, length, txtRec);
						}
						txtRec = "";
						recAddress = address;
						//					cout <<"~~~~~~  "<< address << "   " << txtRec << "   " << label
						//							<< "   " << operation << "   " << operand << endl;
						file.writeAll(address, "", label, operation, operand);
						objectCode = "";
					} else if (objectCode == "noObject") {
						objectCode = "";
						file.writeAll(address, "", label, operation, operand);
					} else if (objectCode == "error") {
						file.writeAll(address, "", label, operation, operand);
						file.writeLine(
								"\t***Error: Base addressing not supported\n");
						ok = false;
					} else {
						file.writeAll(address, objectCode, label, operation,
								operand);
					}
					if (ok) {
						if (txtRec.size() == 0) {
							recAddress = address;
						}
						if (txtRec.size() + objectCode.size() > 60) {
							string length = counter.dectoHex(txtRec.size());
							imFile.writeTxtRecord(address, length, txtRec);
							txtRec = objectCode;
							recAddress = address;
						} else {
							txtRec += objectCode;
						}
					}
				}
				startaddress = address;
				if (startaddress.size() <= 6) {
					for (unsigned int i = 0; i < 6 - startaddress.length();
							i++) {
						startaddress = "0" + startaddress;
					}
				}
				break;
			}
		}

		while (!file.eof()) {
			strexc = readImmidiate(file);
			if (strexc == "Comment") {
				file.writeLine(line);
			} else {
				if (operation[0] == '+') {
//					cout << "~~~~~~~~~~~~  " << address << endl;
					format4.push_back(address);
				}
//				cout << "$$$$$$$$   " << ok << "  " << operation << "  "
//						<< operand << endl;
				string x = tables.toLowerCase(operation);
				if (x != "equ" && x != "org") {
					int length = tables.getLength(operation, operand);
					int curAddress = counter.conHexaToDec(address);
					length += curAddress;
					string nextAddress = counter.dectoHex(length);
//				cout << "~~~~~~~~~~~~   " << line << endl;
					string objectCode = check.format(operation, operand,
							nextAddress);		//call ebtehal
					if (objectCode == "") {
						file.writeAll(address, "", label, operation, operand);
						file.writeLine("\t***Error: Invalid Label\n");
						ok = false;
					} else if (objectCode == "dir") {
						string length = counter.dectoHex(txtRec.size());
						if (txtRec != "") {
							imFile.writeTxtRecord(recAddress, length, txtRec);
						}
						txtRec = "";
						recAddress = address;
//					cout <<"~~~~~~  "<< address << "   " << txtRec << "   " << label
//							<< "   " << operation << "   " << operand << endl;
						file.writeAll(address, "", label, operation, operand);
						objectCode = "";
					} else if (objectCode == "noObject") {
						objectCode = "";
						file.writeAll(address, "", label, operation, operand);
					} else if (objectCode == "error") {
						cout << "!!!!!!!!  " << operation <<"    "<<operand<< endl;
						file.writeAll(address, "", label, operation, operand);
						file.writeLine(
								"\t-_-***Error: Base addressing not supported\n");
						ok = false;
						objectCode = "";
					} else {
						file.writeAll(address, objectCode, label, operation,
								operand);
					}
					if (ok) {
						if (txtRec.size() == 0) {
							recAddress = address;
						}
						if (txtRec.size() + objectCode.size() > 60) {
							string length = counter.dectoHex(txtRec.size());
							imFile.writeTxtRecord(address, length, txtRec);
							txtRec = objectCode;
							recAddress = address;
						} else {
							txtRec += objectCode;
						}
					}
				} else {
					file.writeAll(address, "", label, operation, operand);
				}
			}
		}
		if (ok) {

//		cout << "~~~~~~ " << txtRec << endl;
			if (txtRec.length() > 0) {

				string length = counter.dectoHex(txtRec.size());
				imFile.writeTxtRecord(address, length, txtRec);
			}
			for (unsigned int i = 0; i < format4.size(); i++) {
//			cout << "~~~~~~~~~~~~  " << format4[i] << endl;
				int x = counter.conHexaToDec(format4[i]);
				x++;
				string s = counter.dectoHex(x);
				if (s.length() < 5) {
					for (unsigned int i = 0; i < 5 - s.length(); i++) {
						s = "0" + s;
					}
				}
				imFile.writeLine("M" + s + "^05");
			}
//		cout << "~~~~~~~   " << startaddress << endl;
			imFile.writeLine("E" + startaddress);

		}

	}
	file.close();
	return 0;
}

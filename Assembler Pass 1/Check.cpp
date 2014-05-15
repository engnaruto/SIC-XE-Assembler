/*
 * Check.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#include "Check.h"

using namespace std;
Check::Check(Tables &tables) {
	this->tables = tables;

}
Check::~Check() {

}
string Check::checkAll(string *label, string *operation, string *operand) {

	bool ok;
	string exception = "";
	ok = checkLabel(&(*label));
	if (!ok) {
		cout<<"LABEL ERRORRRRRRRRRRRRRRRR"<<endl;
		exception += "\t***Error: Unavailable or duplicate Symbol\n";
	}
	cout << ">>>>>>Label = " << *label << " Size = " << (*label).size() << endl;
	ok = checkOperation(&(*operation));
	if (!ok) {
		cout<<"OPERATION ERRORRRRRRRRRRRRRRRR"<<endl;
		exception += "\t***Error: Unavailable Mnemonic\n";
	}
	cout << ">>>>>Operation = " << *operation << " Size = " << (*operation).size()
			<< endl;
	ok = checkOperand(&(*operand));
	if (!ok) {
		cout<<"OPERAND ERRORRRRRRRRRRRRRRRR"<<endl;
		exception += "\t***Error: Unavailable Operand\n";
	}
//	cout << "XOXOXOXO  to Operand => " << *operand << "  " << ok << endl;
	cout << ">>>>>>>Operand = " << *operand << " Size = " << (*operand).size() << endl;
//	cout << "OOOOOOOOO Operand => " << *operand << "  " << ok << endl;

	return exception;
}
bool Check::checkLabel(string *label) {
	bool accep = false;
	accep = checkSpaces(*label, 1);
	(*label) = trim(*label);
	if (accep && (*label).size() != 0) {
		int check = checkAtHash(*label);
		if (check != 3) {
			accep = isalpha((*label)[0]);
			for (unsigned int i = 1; i < (*label).length(); i++) {
				if (isalpha((*label)[i]) && i != (*label).length() - 1
						&& accep == true) {
					accep = true;
				} else if (!isalpha((*label)[i])
						&& ((int) (*label)[i] >= 48 && (int) (*label)[i] <= 57)
						&& i != (*label).length() - 1 && accep == true) {
					accep = true;

				} else if ((*label)[i] != ' ' && checkSpaces((*label), 1)) {
					accep = false;
				}
			}
		}
	}
	return accep;
}
bool Check::checkOperation(string *operation) {
	bool ok = checkSpaces((*operation), 2);
//	cout << "MMMMMMMMMMMM Operation => " << *operation << "    "
//			<< (*operation).length() << endl;
	(*operation) = trim((*operation));
//	cout << "NNNNNNNNNNNN Operation => " << *operation << endl;
	string x = toLowerCase(*operation);
//	cout << "XXXXXXXX Operation => " << x << "  OK => " << ok << endl;
	if (ok == true) {
		string dir[6];
		dir[0] = "word";
		dir[1] = "byte";
		dir[2] = "resb";
		dir[3] = "resw";
		dir[4] = "start";
		dir[5] = "end";
//		map<string, string> big;
		if (x.empty() == true) {
			return false;
		}
//		cout << ":P :P :P" << endl;
		if (isalpha(x[0]) == false && x[0] != '+') {
			return false;
		}
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
	}

	return false;
}

bool Check::checkOperand(string *operand) {
	bool ok = checkSpaces((*operand), 0);
	(*operand) = trim((*operand));
	if (ok == true) {
		if ((*operand).at(0) == '\0') {
			return true;
		} else {
//			cout << "ASASASASASASAS  " << (*operand).at(0) << endl;
			if ((*operand).at(0) == '#') {
//				cout << "DFDFDFDFDFDFDF" << endl;
				return checkLabelAndNubmers((*operand).substr(1));
			} else if ((*operand).at(0) == '@') {
//				cout << "ZXZXZXZXZXZXZX" << endl;
				return true; //checkLabel(operand.substr(1),labels);
			} else if ((*operand).find(",") < 100 && (*operand).find(",") > 0) {
//				cout << "CVCVCVCVCVCVCVCV" << endl;
				int pos = (*operand).find(",");
				string str1 = (*operand).substr(0, pos);
				string str2 = (*operand).substr(pos + 1);
				return checkRegister(str1, str2);

			} else if ((*operand).size() > 1
					&& ((*operand).at(1) == ' ' || (*operand).at(1) == '\0')) {
//				cout << "RERERERERERERERERE" << endl;
				if ((*operand).at(0) == 'a' || (*operand).at(0) == 'b'
						|| (*operand).at(0) == 'x' || (*operand).at(0) == 't'
						|| (*operand).at(0) == 's' || (*operand).at(0) == 'l') {
//					cout << "TYTYTYTYTYTYTYT" << endl;
					return true;
				} else {
//					cout << "GHGHGHGHGHGHGHG" << endl;
					return false;
				}
			} else {
//				cout << "QWQWQWQWQWQW" << endl;
				return checkLabelAndNubmers((*operand));
			}
//			cout << "XCXCXCXCXCXCXC" << endl;
		}
//		cout << "YUYUYUYUYUYUYUYU" << endl;
	}
//	cout << "ZDZDZDZDZDZDZDDZ" << endl;
	return false;
}

bool Check::checkOperationOperandMathcing(string operand, string operation) {
	string mapOperand = ""; // opTable[operation].operand;
	bool ok = false;
	if (operand == "-") {
		if (operand.length() == 0) {
			ok = true;
		}
	} else if (mapOperand == "r1") {
		ok = checkRegister(operand);
	} else if (mapOperand == "r1,r2") {
		int pos = operand.find(",");
		string str1 = operand.substr(0, pos);
		string str2 = operand.substr(pos + 1);
		ok = checkRegister(str1) & checkRegister(str2);
	} else if (mapOperand == "r1,n") {
		if (operand.find(",") < 100 && operand.find(",") > 0) {
			int pos = operand.find(",");
			string str1 = operand.substr(0, pos);
			string str2 = operand.substr(pos + 1);
			ok = checkRegister(str1) & isNumber(str2);
		}
	} else if (mapOperand == "m") {
		string s = "";
		if (s == "3/4") {
			if (operand.find(",") < 100 && operand.find(",") > 0) {
				int pos = operand.find(",");
				string str1 = operand.substr(0, pos);
				string str2 = operand.substr(pos + 1);
				ok = (str1 == "x") & (!checkRegister(str2));
			}
		} else {
			int x = checkAtHash(operand);
			if (x == 0 || x == 1) {
				ok = true;
			}
		}
	} else {
		cout << "ERROR IN hashTable.txt >> " << mapOperand << endl;
	}
	return ok;
}
bool Check::checkSpaces(string str, int type) {
	bool valid = true;

	if (str[0] == ' ')
		valid = false;

	for (unsigned int i = 1; i < str.length(); i++) {
		if (str[i] == ' ' && str[i + 1] != ' ' && i != str.length() - 1)
			valid = false;
	}
	if (type == 1) {
		if (str[8] != ' ')
			valid = false;
	}
	if (type == 2) {
		if (str[6] != ' ' || str[7] != ' ')
			valid = false;
	}
	return valid;
}

int Check::checkAtHash(string searchable) {
	string x = toLowerCase(searchable);
	int check1;
	int check2;
	int check = 0;
	int found = 0;
	tables.symTable.count(x);
	if (found > 0) {
		check1 = 1;
		check = 1;
	}
	int found2 = 0;
	tables.opTable.count(x);
	if (found2 > 0) {
		check2 = 2;
		check = 2;
	}
	if (check1 == 1 && check2 == 2) {
		check = 3;
	}
	return check;
}

bool Check::checkHexaNumber(string st) {
	string x = toLowerCase(st);
	if (x.length() % 2 == 1) {
		return false;
	}
	for (unsigned int i = 0; i < x.length(); i++) {
		if ((x.at(i) >= '0' && x.at(i) <= '9')
				|| (x.at(i) >= 'a' && x.at(i) <= 'f')) {
			continue;
		} else {
			return false;
		}
	}
	return true;
}
bool Check::isatSymTable(string label) {
	if (tables.symTable.count(label) > 0) {
		return true;
	} else {
		return false;
	}
}

bool Check::checkLabelAndNubmers(string label) {

	if (label.at(0) >= '0' && label.at(0) <= '9') {
		for (unsigned int i = 1; i < label.length(); i++) {
			if (label.at(i) >= '0' && label.at(i) <= '9') {
				continue;
			} else {
				return false;
			}
		}
	} else if (label.at(0) == 'x' && (int) label.at(1) == 39) {
		if ((int) label.at(8) == 39) {
			return checkHexaNumber(label.substr(2, 6));
		} else {
			return false;
		}

	} else if (label.at(0) == 'c' && (int) label.at(1) == 39) {
		if ((int) label.at(label.length() - 1) == 39) {
			return true;
		} else {
			return false;
		}
	} else {
		return true; //checkLabel(label,labels);
	}

	return true;
}

bool Check::checkRegister(string str1, string str2) {
	string x1 = toLowerCase(str1);
	string x2 = toLowerCase(str2);
	if (x1 == "a" || x1 == "b" || x1 == "x" || x1 == "t" || x1 == "s"
			|| x1 == "l") {
		if (x2 == "a" || x2 == "b" || x2 == "x" || x2 == "t" || x2 == "s"
				|| x2 == "l") {
			return true;
		} else {
			return false;
		}
	} else {
		if (x2 == "x") //&&checkLabel(str1,labels)==true)
			return true;
		else
			return false;
	}
}

bool Check::checkRegister(string str1) {
	string x = toLowerCase(str1);
	if (x == "a" || x == "b" || x == "x" || x == "t" || x == "s" || x == "l") {
		return true;
	}
	return false;
}

bool Check::isNumber(string st) {
	if (st.length() == 0)
		return false;
	for (unsigned int i = 0; i < st.length(); i++) {
		if (st.at(i) >= '0' && st.at(i) <= '9')
			continue;
		else
			return false;
	}
	return true;
}

string Check::trim(string input) {
	string output = "";

	for (unsigned int i = 0; i < input.length(); i++) {
		if (input[i] != ' ' && input[i] != '\t') {
			output = output + input[i];
		}
	}
	return output;
}
string Check::toLowerCase(string input) {
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

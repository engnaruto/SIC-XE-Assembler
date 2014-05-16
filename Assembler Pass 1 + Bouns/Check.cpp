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
string Check::checkAll(vector<string> arr, string *label, string *operation,
		string *operand, string *comment) {

//	bool ok;
	string exception = "";
//	ok = checkLabel(&(*label), &exception);
//	if (!ok) {
//		cout << "LABEL ERRORRRRRRRRRRRRRRRR" << endl;
//		exception += "\t***Error: Unavailable or duplicate Symbol\n";
//	}
//	ok = checkOperation(&(*operation), &exception);
//	if (!ok) {
//		cout << "OPERATION ERRORRRRRRRRRRRRRRRR" << endl;
//		exception += "\t***Error: Unavailable Mnemonic\n";
//	}
//	ok = checkOperand(&(*operand), &exception);
//	if (!ok) {
//		cout << "OPERAND ERRORRRRRRRRRRRRRRRR" << endl;
//		exception += "\t***Error: Unavailable Operand\n";
//	}
//	ok = checkOperationOperandMathcing((*operation), (*operand), &exception);

	return exception;
}
bool Check::checkLabel(string *label, string *exception) {
	bool accep = false;
	accep = checkSpaces(*label, 1);
	(*label) = trim(*label);
	string x = toLowerCase(*label);
	if (accep && (x).size() != 0 && !(x).empty()) {
		int check = checkAtHash(x);
		if (check == 0) {
			accep = isalpha((x)[0]);
			for (unsigned int i = 0; i < (x).length(); i++) {
				if (isalpha((x)[i]) && i != (x).length() - 1 && accep == true) {
					accep = true;
				} else if (!isalpha((x)[i])
						&& ((int) (x)[i] >= 48 && (int) (x)[i] <= 57)
						&& i != (x).length() - 1 && accep == true) {
					accep = true;

				} else if (x[i] == ' ') {
					accep = false;
					break;
				}
			}
		} else {
			accep = false;
		}
	} else {
		accep = true;
	}
	return accep;
}
bool Check::checkOperation(string *operation, string *exception) {
	bool ok = checkSpaces((*operation), 2);
	(*operation) = trim((*operation));
	string x = toLowerCase(*operation);
//	cout << "-----------OPERATION " << *operation << "      " << ok << endl;
	if (ok == true) {
		string dir[6];
		dir[0] = "word";
		dir[1] = "byte";
		dir[2] = "resb";
		dir[3] = "resw";
		dir[4] = "start";
		dir[5] = "end";
		if (x.empty() == true) {
			return false;
		}
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

bool Check::checkOperand(string *operand, string *exception) {
	bool ok = checkSpaces((*operand), 0);
	(*operand) = trim((*operand));

	if (ok == true && !(*operand).empty()) {
		if ((*operand).at(0) == '\0') {
			return true;
		} else {
			if ((*operand).at(0) == '#') {
				return checkLabelAndNubmers((*operand).at(0),
						(*operand).substr(1), &(*exception));
			} else if ((*operand).at(0) == '@') {
				return true; //checkLabel(operand.substr(1),labels);
			} else if ((*operand).find(",") < 100 && (*operand).find(",") > 0) {
				int pos = (*operand).find(",");
				string str1 = (*operand).substr(0, pos);
				string str2 = (*operand).substr(pos + 1);
				return checkRegister(str1, str2, &(*exception));
			} else if ((*operand).size() > 1
					&& ((*operand).at(1) == ' ' || (*operand).at(1) == '\0')) {
				if ((*operand).at(0) == 'a' || (*operand).at(0) == 'b'
						|| (*operand).at(0) == 'x' || (*operand).at(0) == 't'
						|| (*operand).at(0) == 's' || (*operand).at(0) == 'l') {
					return true;
				} else {
					return false;
				}
			} else if ((*operand).at(0) == '=') {
				return checkLabelAndNubmers((*operand).at(0),
						(*operand).substr(1), &(*exception));
			} else if ((*operand).at(0) == '*') {
				return true;
			} else {
				return checkLabelAndNubmers('=', (*operand), &(*exception));
			}
		}
	}
	if ((*operand).empty()) {
//		cout << "ASASASASASASAS  " << (*operand) << "     " << ok << endl;
		return true;
	}
	return false;
}

bool Check::checkOperationOperandMathcing(string operation, string operand,
		string *exception) {
	string mapOperand = tables.opTable[operation].operand;
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
	string t = trim(str);
	if (type == 1) {
		if (str[8] != ' ')
			valid = false;
		if (t.empty()) {
			valid = true;
		}
	}
	string x = trim(str);
	x = toLowerCase(x);
	if (type == 2 && (tables.opTable[x].operand != "-" || x == "end")) {
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

bool Check::isHexaNumber(string st, string * exception) {
	string x = toLowerCase(st);
	if (x.length() % 2 == 1) {
		*exception += "\t***Error: Invalid hex number\n";
		return false;
	}
	for (unsigned int i = 0; i < x.length() && x.at(i) != ' '; i++) {
		if ((x.at(i) >= '0' && x.at(i) <= '9')
				|| (x.at(i) >= 'a' && x.at(i) <= 'f') || (int) x.at(i) == 39) {
			continue;
		} else {
			*exception += "\t***Error: Invalid hex number\n";

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

bool Check::checkLabelAndNubmers(char c, string label, string * exception) {

	if (label.at(0) >= '0' && label.at(0) <= '9') {
		for (unsigned int i = 1; i < label.length(); i++) {
			if (label.at(i) >= '0' && label.at(i) <= '9') {
				continue;
			} else {
				*exception += "\t***Error: Invalid number\n";

				return false;
			}
		}
	} else if (label.at(0) == 'x' && (int) label.at(1) == 39 && c == '=') {
		if (label.length() - 3 % 2 == 0) {
			return isHexaNumber(label.substr(2), exception);

		} else {
			*exception += "\t***Error: Invalid hex number";
			return false;
		}

	} else if (label.at(0) == 'c' && (int) label.at(1) == 39 && c == '=') {
		if ((int) label.at(label.length() - 1) == 39) {
			return true;
		} else {
			*exception += "\t***Error: Invalid expression (')missing\n";
			return false;
		}
	} else if ((label.at(0) == 'x' && (int) label.at(1) == 39 && c != '=')
			|| (label.at(0) == 'c' && (int) label.at(1) == 39 && c != '=')) {
		*exception += "\t***Error: Invalid expression\n";

		return false;
	} else {
		return true; //checkLabel(label,labels);
	}

	return true;
}

bool Check::checkRegister(string str1, string str2, string *exception) {
	string x1 = toLowerCase(str1);
	string x2 = toLowerCase(str2);
	if (x1 == "a" || x1 == "b" || x1 == "x" || x1 == "t" || x1 == "s"
			|| x1 == "l") {
		if (x2 == "a" || x2 == "b" || x2 == "x" || x2 == "t" || x2 == "s"
				|| x2 == "l") {
			return true;
		} else {
			*exception += "\t***Error: Invalid register\n";

			return false;
		}
	} else {
		if (x2 == "x") //&&checkLabel(str1,labels)==true)
			return true;
		else {
			*exception += "\t***Error: Invalid register must be X\n";

			return false;

		}
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

Tables Check::getTables() {
	return tables;
}

void Check::split(vector<string>arr, string *_label, string *_operation,
		string *_operand, string *_comment) {
	*_label = "";
	*_operation = "";
	*_operand = "";
	*_comment = "";

	string ex = "";
	for (unsigned int i = 0; i < arr.size(); i++) {
		string tmp = arr[i];
		if (tmp[0] == '.') {
			for (unsigned i = 0; i < arr.size(); i++) {
				*_comment = *_comment + arr[i];
			}
		} else {
			bool ch = checkOperation(&arr[i], &ex);
			if (ch) {
				string x = toLowerCase(arr[i]);
				if (tables.opTable[x].operand == "-" || x == "end") {

					for (unsigned int j = i + 1; j < arr.size(); j++) {
						*_comment = *_comment + arr[j];
						i++;
					}
				} else {
					*_operand = arr[i + 1];

					for (unsigned int j = i + 2; j < arr.size(); j++) {
						*_comment = *_comment + arr[j];
						i++;
					}

				}
			} else {
				*_label = arr[i];
			}
		}

	}
}

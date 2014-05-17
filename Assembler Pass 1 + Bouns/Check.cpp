/*
 * Check.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#include "Check.h"

using namespace std;
Check::Check(Tables *tables) {
	this->tables = (tables);

}
Check::~Check() {

}
string Check::checkAll(string address, string *label, string *operation,
		string *operand) {

	bool ok;
	string exception = "";
	ok = checkLabel(address, &(*label), &exception);
	ok = checkOperation(&(*operation), &exception);
	if (ok) {
		ok = checkOperand(&(*operand), &exception);
		if (ok) {
			ok = checkOperationOperandMathcing((*operation), (*operand),
					&exception);
		}
	}

	return exception;
}
bool Check::checkLabel(string address, string *label, string *exception) {
	cout << "label   " << *label << endl;
	bool accep = true;
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

				} else {
					accep = false;
					break;
				}
			}
			tables->symTable.insert(pair<string, string>(x, address));
		} else {
			if (check == 2) {
				*exception += "\t***Error: Invalid label name\n";

			} else {
				*exception += "\t***Error: Duplicate label\n";

			}
			accep = false;
		}
	} else {
		accep = true;
	}
	return accep;
}
bool Check::checkOperation(string *operation, string *exception) {
	bool ok = true;
	string x = toLowerCase(*operation);
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
		int found = tables->opTable.count(x);
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
	if (!ok) {
		*exception += "\t***Error: Invalid operand\n";
		return false;
	}
	(*operand) = trim((*operand));

	if (ok == true && !(*operand).empty()) {
		if ((*operand).length() == 0) {
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
			} else if ((*operand).size() == 1) {
				if ((*operand).at(0) == 'a' || (*operand).at(0) == 'b'
						|| (*operand).at(0) == 'x' || (*operand).at(0) == 't'
						|| (*operand).at(0) == 's' || (*operand).at(0) == 'l') {
					return true;
				} else if ((*operand).at(0) != '*') {
					return checkLabelAndNubmers('=', (*operand), &(*exception));
				} else {
					return true;
				}
			} else if ((*operand).at(0) == '=') {
				return checkLabelAndNubmers((*operand).at(0),
						(*operand).substr(1), &(*exception));
			} else if ((*operand).at(0) == '*') {
				return true;
			} else if ((*operand).find("'") < 50 && (*operand).find("'") > 0) {
//				cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				return checkByte((*operand), &(*exception));
			} else {
				return checkLabelAndNubmers('=', (*operand), &(*exception));

			}
		}
	}
	if ((*operand).empty()) {
		return true;
	}
	return false;
}

bool Check::checkOperationOperandMathcing(string operation, string operand,
		string *exception) {
	bool ok = false;
	operation = toLowerCase(operation);
	operand = toLowerCase(operand);
	string mapOperand = tables->opTable[operation].operand;
	if (operation == "start") {
		if (checkAddress(operand, &(*exception))) {
			ok = true;
		} else {
			*exception += "\t***Error: Invalid address in operand\n";
		}
	} else if (operation == "word" || operation == "resb"
			|| operation == "resw") {
//		cout << "~~~~~~~~~~~   " <<operation<<"    "<< operand.size() << endl;
		if (isNumber(operand)) {
			ok = true;
		} else {
			*exception += "\t***Error: Invalid number\n";
		}
	} else if (operation == "end") {
		ok = true;
		if (operand.empty()) {
		} else {
//			*exception += "\t***Error: Extra Characters after END\n";
		}
	} else if (operation == "rsub") {
		ok = true;
		if (!operand.empty()) {
			ok = false;
			*exception += "\t***Error: Invalid operand\n";

		}

	} else if (operation == "byte") {
//CHECK ARRAY OR HEXA
//		string s = "";
		if (checkByte(operand, &(*exception))) {
			ok = true;
		}
	} else if (mapOperand == "-") {
		if (operand.length() == 0) {
			ok = true;
		} else {
			*exception += "\t***Error: Invalid operand\n";
		}
	} else if (mapOperand == "r1") {
		if (operand[0] == 'x') {
			ok = true;
		} else {
			*exception += "\t***Error: Invalid register in operand\n";
		}

	} else if (mapOperand == "r1,r2") {
		if (operand.find(",") < 100 && operand.find(",") > 0) {
			int pos = operand.find(",");
			string str1 = operand.substr(0, pos);
			string str2 = operand.substr(pos + 1);
			ok = true;
			if (!checkRegister(str1) || !checkRegister(str2)) {
				*exception += "\t***Error: Illegal address for register";
				ok = false;
			}
		} else {
			*exception += "\t***Error: Missing comma in operand";
			ok = false;
		}
	} else if (mapOperand == "r1,n") {
		if (operand.find(",") < 100 && operand.find(",") > 0) {
			int pos = operand.find(",");
			string str1 = operand.substr(0, pos);
			string str2 = operand.substr(pos + 1);
			ok = true;
			if (!checkRegister(str2)) {
				*exception += "\t***Error: Illegal address for register";
				ok = false;
			}
			if (!isNumber(str2)) {
				ok = false;
				*exception += "\t***Error: Invalid n";
			}
		} else {
			*exception += "\t***Error: Missing comma in operand";
			ok = false;
		}

	} else if (mapOperand == "m") {
		string s = "";
		//  #   @

		if (s == "3/4") {
			if (operand.find(",") < 100 && operand.find(",") > 0) {
				int pos = operand.find(",");
				string str1 = operand.substr(0, pos);
				string str2 = operand.substr(pos + 1);
				if (str2 != "x") {
					*exception += "\t***Error: Illegal address for register";
					ok = false;
				}
				ok &= (!checkRegister(str1));
				if (ok) {
					*exception += "\t***Error: Illegal address for symbol";
				}
			} else {
				*exception += "\t***Error: Missing comma in operand";
			}
		} else if (operand == "*") {
			ok = true;
		} else {
			int x = checkAtHash(operand);
			if (x == 0 || x == 1) {
				ok = true;
			}
		}
	} else {
//		cout << "MMMMMMMMMMMM   " << operation << "   " << operand
//				<< "   ok =   " << ok << endl;
		*exception += "\t***Error: Undefined operand type\n";
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
	if (type == 2 && (tables->opTable[x].operand != "-" && x != "end")) {
//cout <<"INNNNNNNN<<<<   "<<x<<endl;
		if (str[6] != ' ' || str[7] != ' ')
			valid = false;
	}
	return valid;
}

bool Check::checkByte(string oper, string *exception) {
	if (oper.at(0) == 'c' || oper.at(0) == 'C') {
		return checkLabelAndNubmers('=', oper, &(*exception));
	} else if (oper.at(0) == 'x' || oper.at(0) == 'X') {
		return checkLabelAndNubmers('=', oper, &(*exception));
	} else if (oper.find("'") < 50 && oper.find("'") > 0) {
		*exception += "\t***Error: Invalid symbol\n";
		return false;
	}
	return true;
}

int Check::checkAtHash(string searchable) {
	string x = toLowerCase(searchable);
	int check1;
	int check2;
	int check = 0;
	int found = tables->symTable.count(x);
	if (found > 0) {
		check1 = 1;
		check = 1;
	}
	int found2 = tables->opTable.count(x);
	if (found2 > 0) {
		check2 = 2;
		check = 2;
	}
	if (check1 == 1 && check2 == 2) {
		check = 3;
	}
	return check;
}
bool Check::checkAddress(string st, string * exception) {
	string x = toLowerCase(st);
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
bool Check::isHexaNumber(string st, string * exception) {
	string x = toLowerCase(st);
//	cout << "@@@@@@   " << x << endl;
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
	if (tables->symTable.count(label) > 0) {
		return true;
	} else {
		return false;
	}
}

bool Check::checkLabelAndNubmers(char c, string label, string *exception) {

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

		if ((label.length() - 3) % 2 == 0) {
//			cout << "INNNNNNNNNNN   " << label.size() << endl;
			return isHexaNumber(label.substr(2, label.size() - 3), exception);

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
	} else if (label.at(0) == '-' && c == '#') {
		*exception += "\t***Error: Invalid expression no -ve number \n";
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
		if ((st.at(i) >= '0' && st.at(i) <= '9') || (st.at(0) == '-')) {
			continue;
		} else {
			return false;
		}
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

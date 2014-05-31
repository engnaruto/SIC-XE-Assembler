/*
 * Check.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#include "Check.h"
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

string arr_addresses[10];
string base = "";
bool experrsion = false;
string adress_expression = "";
Check::Check(Tables *tables) {
	this->tables = (tables);

}
Check::~Check() {

}
string Check::checkAll(string address, string *label, string *operation,
		string *operand, LocCounter*loc) {

	bool ok;
	string exception = "";
	ok = checkLabel(address, &(*label), &exception);
	ok = checkOperation(&(*operation), &exception);
	if (ok) {
		ok = checkOperand(&(*operand), &exception);
		if (ok) {
			ok = checkOperationOperandMatching((*operation), (*operand),
					&exception);
		}
	}
//	EQU((*label), (*operation), (*operand), (*loc), &exception);
	ORG((*operation), (*operand), &(*loc), &exception);
//	cout << "~~~~~~~  " << endl;
	return exception;
}
bool Check::checkLabel(string address, string *label, string *exception) {
	bool accep = false;
	accep = checkSpaces(*label, 1);
	if (!accep) {
		*exception += "\t***Error: Invalid label name\n";
		return false;
	}
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
//			if (x.size() > 1 && x.at(x.length() - 1) == '+') {
//				x = x.substr(0, x.length() - 1);
//			}
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
	bool ok = checkSpaces((*operation), 2);
	if (!ok) {
//	cout << "-----------OPERATION " << *operation << "      " << ok << endl;
		*exception += "\t***Error: Invalid Operation\n";
		return false;
	}
	(*operation) = trim((*operation));
	string x = toLowerCase(*operation);
	if (x == "+rsub") {
		*exception += "\t***Error: REUB cannot be format 4 instruction\n";
	}

	if (x[0] == '+') {
		x = x.substr(1);
	}
	if (ok == true) {
		if (x == "base" || x == "use" || x == "ltorg") {
			*exception += "\t***Error: Not supported directive\n";
		}
//		cout << "  oper  " << x << endl;
		string dir[9];
		dir[0] = "word";
		dir[1] = "byte";
		dir[2] = "resb";
		dir[3] = "resw";
		dir[4] = "start";
		dir[5] = "end";
		dir[6] = "equ";
		dir[7] = "rsub";
		dir[8] = "org";
		if (x.empty() == true || isalpha(x[0]) == false) {
			*exception += "\t***Error: Invalid Operation\n";
			return false;
		}
//		if (isalpha(x[0]) == false) {
//			*exception += "\t***Error: Invalid Operation\n";
//			return false;
//		}
//		if (x[0] == '+') {
//			string tmp = "";
//			tmp.assign(x.begin() + 1, x.end());
//			x.assign(tmp);
//		}
		int found = checkAtHash(x);
//		int found = tables->opTable.count(x);
//		cout << "found = " << found << "     " << x << endl;
		if (found > 1) {
			return true;
		}
		int i;
		for (i = 0; i < 9; i++) {
			if (x == dir[i]) {
//				cout << " vbvbvbvbvbv   " << x;
				return true;
			}
		}
	}
	*exception += "\t***Error: Invalid operation\n";
	return false;
}

bool Check::checkOperand(string *operand, string *exception) {
	bool ok = true;
//	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
//	(*operand) = trim((*operand));
	(*operand) = trim2((*operand));
	if (ok == true && !(*operand).empty()) {
		if ((*operand)[0] == ' ') {
			*exception += "\t***Error: Invalid operand\n";
			return false;
		} else if ((*operand).length() == 0) {
			return true;
		} else if ((*operand).at(0) == '#') {
			return checkLabelAndNubmers((*operand).at(0), (*operand).substr(1),
					&(*exception));
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
			return checkLabelAndNubmers((*operand).at(0), (*operand).substr(1),
					&(*exception));
		} else if ((*operand).at(0) == '*') {
			return true;
		} else if ((*operand).find("'") < 50 && (*operand).find("'") > 0) {
//				cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			return checkByte((*operand), &(*exception));
		} else {
			return checkLabelAndNubmers('=', (*operand), &(*exception));
		}
	}
	if ((*operand).empty()) {
		return true;
	}
	*exception += "\tError: Invalid operand\n";
	return false;
}

bool Check::checkOperationOperandMatching(string operation, string operand,
		string *exception) {
	bool ok = false;
	operation = toLowerCase(operation);
	operand = toLowerCase(operand);
	if (operation[0] == '+') {
		string tmp = "";
		tmp.assign(operation.begin() + 1, operation.end());
		operation.assign(tmp);
	}
	if (operand[0] == '@' || operand[0] == '#') {
		string tmp = "";
		tmp.assign(operand.begin() + 1, operand.end());
		operand.assign(tmp);
	}
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
			*exception += "\t***Error: Invalid number2\n";
		}
	} else if (operation == "end" || operation == "equ" || operation == "org") {
		ok = true;
//		if (operand.empty()) {
//		} else {
//			cout<<"\t***Error: Extra Characters after END\n";
//		}

	} else if (operation == "rsub") {
////			ok = false;
//		if (operand.empty()) {
//			ok = true;
//		} else {
//			*exception += "\t***Error: Invalid operand\n";
//		}

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
		if (checkRegister(operand)) {
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
//		string s = tables->opTable[operation].format;
		//  #   @

//		if (s == "3/4") {
		if (operand.find(",") < 100 && operand.find(",") > 0) {
			int pos = operand.find(",");
			string str1 = operand.substr(0, pos);
			string str2 = operand.substr(pos + 1);
			if (str2 != "x") {
				*exception += "\t***Error: Illegal address for register\n";
				ok = false;
			}
//			ok &= (!checkRegister(str1));
////			int x = checkAtHash(str1);
//			if (x == 2) {
//				ok = false;
//			}
//			if (!ok) {
//				*exception += "\t***Error: Illegal symbol name\n";
//			}
//			} else {
//				*exception += "\t***Error: Missing comma in operand";
//			}
		} else if (operand == "*") {
			ok = true;
		} else {
//			int x = checkAtHash(operand);
//			if (x == 0 || x == 1) {
//				ok = true;
//			} else {
//				*exception += "\t***Error: Illegal symbol name\n";
//			}
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
	unsigned int i;
	if (type == 2) {
		if (str[0] != ' ' && str[0] != '+') {
			return false;
		}
		string x = trim(str);
		x = toLowerCase(x);
		if (tables->opTable[x].operand != "-" && x != "end") {
			if (str[7] != ' ' || str[8] != ' ') {
//				cout << "######  /" << str << endl;
				valid = false;
			}
		}
		i = 1;
	} else {
		i = 0;
	}
	for (; i < str.length(); i++) {
		if (str[i] == ' ' && str[i + 1] != ' ' && i != str.length() - 1
				&& str[8] != '+')
			valid = false;
	}
	string t = trim(str);
	if (type == 1 && t.empty()) {
		valid = true;
//		cout << "INNNNNNNN<<<<   " << t << endl;
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
//		cout << "~~~~~~~~~  found2 = " << found2 <<" /   x = "<<x<< endl;
	int found2 = tables->opTable.count(x);
	if (found2 > 0) {
		if (tables->opTable.at(x).opcode.size() != 0) {
			check2 = 2;
			check = 2;
		}
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
//		if (label.length() > 4) {
//			*exception += "\t***Error: Invalid number\n";
//			return false;
//		}
		for (unsigned int i = 1; i < label.length(); i++) {
			if ((label.at(i) >= '0' && label.at(i) <= '9') || label.at(i) == '-'
					|| label.at(i) == '+' || label.at(i) == '/'
					|| label.at(i) == '*') {
				continue;
			} else {
				*exception += "\t***Error: Invalid number\n";

				return false;
			}
		}
	} else if (label.at(0) == 'x' && (int) label.at(1) == 39 && c == '=') {

		if ((label.length() - 3) % 2 == 0) {
// cout << "INNNNNNNNNNN " << label.size() << endl;
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

string Check::trim2(string input) {
//	cout << "##########" << endl;
	string output = "";
	int x = 0;
	for (unsigned int i = input.length() - 1; i >= 0; i--) {
		if (input[i] != ' ' && input[i] != '\t') {
			x = i;
			break;
//			continue;
		}
	}
	output = input.substr(0, x + 1);
//	cout << "~~~~~~~~ " << output << "/   " << input << "/ " << input[x]
//			<< endl;
	return output;
}
string Check::toLowerCase(string input) {
	unsigned int i;
	string tmp = "";
	for (i = 0; i < input.length(); i++) {
		char c = input[i];
//		cout << "~~~~~~  " << c << endl;
		int n = tolower(c);
		char d = char(n);
		tmp = tmp + d;
	}
	return tmp;
}
string Check::evaluate(string oper, LocCounter loc, string *exception) {
	oper = toLowerCase(oper);
	if (oper.find("+") < 20 && oper.find("+") > 0) {

		int x = oper.find("+");
		string lab = oper.substr(0, x);
		string op = oper.substr(x + 1);
		if (isatSymTable((lab)) && (isNumber(op) == true)) {
			string address = tables->symTable.at(lab);
			int add = loc.conHexaToDec(address);
			int plus = atoi(oper.substr(x + 1).c_str());
			add = add + plus;
			string result = dectoHex(add);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if ((isNumber(lab) == true) && (isNumber(op) == true)) {
			int val1 = atoi(lab.c_str());
			int val2 = atoi(op.c_str());
			int val = val1 + val2;
			string result = dectoHex(val);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if (isatSymTable((lab)) && (isNumber(op) == false)) {
			*exception += "\t***Error: Can't add t relative labels\n";
			return "error";
		} else if (lab == "*" && (isNumber(op) == false)) {
			*exception += "\t***Error: Can't add t relative labels\n";
			return "error";
		} else if (lab == "*" && (isNumber(op) == true)) {
			string address = loc.getAddressLabel();
			int add = loc.conHexaToDec(address);
			int plus = atoi(oper.substr(x + 1).c_str());
			add = add + plus;
			string result = dectoHex(add);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else {
			*exception += "\t***Error: Undefined Symbol\n";
			return "error";

		}

	} else if (oper.find("-") < 20 && oper.find("-") > 0) {
		int x = oper.find("-");
		string lab = oper.substr(0, x);
		string op = oper.substr(x + 1);
		if (isatSymTable((lab)) && (isNumber(op) == true)) {
			string address = tables->symTable.at(lab);
			int add = loc.conHexaToDec(address);
			int munes = atoi(oper.substr(x + 1).c_str());
			add = add - munes;
			if (add < 0) {
				*exception += "\t***Error: Address can't be negative\n";

				return "error";
			}
			string result = dectoHex(add);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if (isatSymTable((lab)) && (isNumber(op) == false)) {
			string address1 = tables->symTable.at(lab);
			string address2 = tables->symTable.at(op);
			int add1 = loc.conHexaToDec(address1);
			int add2 = loc.conHexaToDec(address2);
			int munes = add1 - add2;
			if (munes < 0) {
				*exception += "\t***Error: Address can't be negative\n";

				return "error";
			}
			string result = dectoHex(munes);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if ((isNumber(lab) == true) && (isNumber(op) == true)) {
			int val1 = atoi(lab.c_str());
			int val2 = atoi(op.c_str());
			int val = val1 - val2;
			if (val < 0) {
				*exception += "\t***Error: Address can't be negative\n";

				return "error";
			}
			string result = dectoHex(val);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if (lab == "*" && (isNumber(op) == false)) {
			string address1 = loc.getAddressLabel();
			string address2 = tables->symTable.at(op);
			int add1 = loc.conHexaToDec(address1);
			int add2 = loc.conHexaToDec(address2);
			int munes = add1 - add2;
			if (munes < 0) {
				*exception += "\t***Error: Address can't be negative\n";

				return "error";
			}
			string result = dectoHex(munes);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if (lab == "*" && (isNumber(op) == true)) {
			string address = loc.getAddressLabel();
			int add = loc.conHexaToDec(address);
			int munes = atoi(oper.substr(x + 1).c_str());
			add = add - munes;
			if (add < 0) {
				*exception += "\t***Error: Address can't be negative\n";

				return "error";
			}
			string result = dectoHex(add);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else {
			*exception += "\t***Error: Undefined Symbol\n";
			return "error";

		}
	} else if (oper.find("*") < 20 && oper.find("*") > 0) {
		int x = oper.find("*");
		string lab = oper.substr(0, x);
		string op = oper.substr(x + 1);
		if (isatSymTable((lab)) && (isNumber(op) == true)) {
			string address = tables->symTable.at(oper);
			int add = loc.conHexaToDec(address);
			int multi = atoi(oper.substr(x + 1).c_str());
			add = add * multi;
			string result = dectoHex(add);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if ((isNumber(lab) == true) && (isNumber(op) == true)) {
			int val1 = atoi(lab.c_str());
			int val2 = atoi(op.c_str());
			int val = val1 * val2;
			string result = dectoHex(val);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if (lab == "*" && (isNumber(op) == false)) {
			*exception += "\t***Error: Can't add t relative labels\n";
			return "error";
		} else if (lab == "*" && (isNumber(op) == true)) {
			string address = loc.getAddressLabel();
			int add = loc.conHexaToDec(address);
			int mult = atoi(oper.substr(x + 1).c_str());
			add = add * mult;
			string result = dectoHex(add);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if (isatSymTable((lab)) && (isNumber(op) == false)) {
			*exception += "\t***Error: Can't multiply t relative labels\n";
			return "error";
		} else {
			*exception += "\t***Error: Undefined Symbol\n";
			return "error";

		}

	} else if (oper.find("/") < 20 && oper.find("/") > 0) {
		int x = oper.find("/");
		string lab = oper.substr(0, x);
		string op = oper.substr(x + 1);
		if (isatSymTable((lab)) && (isNumber(op) == true)) {
			string address = tables->symTable.at(lab);
			int add = loc.conHexaToDec(address);
			int div = atoi(oper.substr(x + 1).c_str());
			add = (int) (add / div);
			string result = dectoHex(add);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if ((isNumber(lab) == true) && (isNumber(op) == true)) {
			int val1 = atoi(lab.c_str());
			int val2 = atoi(op.c_str());
			int val = val1 / val2;
			string result = dectoHex(val);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if (lab == "*" && (isNumber(op) == false)) {
			*exception += "\t***Error: Can't add t relative labels\n";
			return "error";
		} else if (lab == "*" && (isNumber(op) == true)) {
			string address = loc.getAddressLabel();
			int add = loc.conHexaToDec(address);
			int div = atoi(oper.substr(x + 1).c_str());
			add = add / div;
			string result = dectoHex(add);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else if (isatSymTable((lab)) && (isNumber(op) == false)) {
			*exception += "\t***Error: Can't divide t relative labels\n";
			return "error";
		} else {
			*exception += "\t***Error: Undifined Symbol\n";
			return "error";
		}

	} else {
		if (isatSymTable((oper))) {
			string address = tables->symTable.at(oper);
//		cout << "!!!!!!!!!!!!!!!!!!  "<<address << endl;
			return address;
		} else if (isNumber(oper)) {

			int val = atoi(oper.c_str());
//			cout << "~~~~~~~~~~~~~~~~~~~~~~~~    number " << val << endl;
			string result = dectoHex(val);
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;

		} else if (oper == "*") {
			string result = loc.getAddressLabel();
			if (result.length() < 5) {
				for (unsigned int i = 0; result.length() < 5; i++) {
					result = "0" + result;
				}
			}
			return result;
		} else {
			*exception += "\t***Error: Undefined Symbol\n";
			return "error";
		}
	}
	return "error";
}

void Check::ORG(string operat, string oper, LocCounter *loc,
		string *exception) {
	string org = toLowerCase(operat);
	org = trim(org);
	oper = trim(oper);
	if (org == "org") {
		string result = evaluate(oper, (*loc), exception);
		if (result != "error") {

			cout << "~~~~~~   " << (*loc).getAddressLabel() << endl;
			(*loc).setCounter(result);
		}
	}
}
void Check::EQU(string lab, string operat, string oper, LocCounter loc,
		string * exception) {
//	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~@@@@@  " << operat << endl;
	string equ = toLowerCase(operat);
	equ = trim(equ);
	oper = trim(oper);
	if (equ == "equ") {
		string result = evaluate(oper, loc, exception);
//		cout << "in here " << result << endl;
		tables->symTable[toLowerCase(lab)] = result;
//		tables->symTable.insert(pair<string, string>(toLowerCase(lab), result));
//		tables->symTable.insert(pair<string, string>(toLowerCase(lab), result));
//		cout << lab << " " << result << endl;
	}

//	return "";

}
//string Check::EQU(string operat, string oper, LocCounter loc,
//		string * exception) {
//	string equ = toLowerCase(operat);
//	equ = trim(equ);
//	oper = trim(oper);
//	if (equ == "equ") {
//		if (isNumber(oper) == true)
//			return NULL;
//		string result = evaluate(oper, loc, exception);
//		return result;
//	}
//	return "";
//}

int Check::dec_to_binary(int dec) {
	int bin = 0, pos = 1;
	while (dec > 0) {
		bin = bin + (dec % 2) * pos;
		dec = dec / 2;
		pos *= 10;
	}
	return bin;
}

int Check::binary_to_dec(int bin) {
	int dec = 0, pos = 0;
	int factor = 1;

	while (bin > 0) {
		if ((bin % 10) == 1) {
			dec += factor;
		}
		bin /= 10;
		pos++;
		factor = factor * 2;
	}

	return dec;
}
string Check::opCodeFor4(string operation, string operand, string address,
		string curaddress) {
	operand = toLowerCase(operand);
	string small_operation = toLowerCase(operation);
	small_operation = small_operation.substr(1);
	string result = "";
	string op = tables->opTable.at(small_operation).opcode;
	int op_dec = conHexaToDec(op);
	int op_bin = dec_to_binary(op_dec);
	string op_binstr = convertIntToString(op_bin);

	char n = '0';
	char i = '0';
	if (operand[0] == '@') {
		n = '1';
	}
	if (operand[0] == '#') {
		i = '1';
	}
	if (n == '0' && i == '0') {
		n = '1';
		i = '1';
	}
	if (op_binstr.length() == 1) {
		op_binstr = '0' + op_binstr;
	}

	op_binstr[op_binstr.length() - 1] = i;
	op_binstr[op_binstr.length() - 2] = n;
	int op_binEdit = atoi(op_binstr.c_str());
	int op_decEdit = binary_to_dec(op_binEdit);
	string op_hexEdit = "";
	op_hexEdit = dectoHex(op_decEdit);

	cout << "  op   " << op_hexEdit << "  " << operation << endl;
	if (op_hexEdit.length() == 1) {
		op_hexEdit = '0' + op_hexEdit;
	}
	result = result + op_hexEdit;

	for (unsigned int i = 0; i < operand.length(); i++) {
		if (operand[i] == ',') {
			result = result + "9";
			break;
		}
	}
	result = result + "1";

	// operand field modified
	if (operand[0] == '#' || operand[0] == '@') {
		string tmp = "";
		tmp.assign(operand.begin() + 1, operand.end());
		operand.assign(tmp);
	}
	string tmp = "";
	for (unsigned int i = 0; i < operand.length(); i++) {
		if (operand[i] == ',') {
			break;
		} else {
			tmp = tmp + operand[i];
		}
	}
	operand.assign(tmp);
	if (operand == "*") {
		address = curaddress;
		result = result + address;
		return result;
	}

	int x = tables->symTable.count(operand);
	if (experrsion) {
		result = result + adress_expression;
	} else if (x > 0) {
		string distin = tables->symTable.at(operand);

		result = result + distin;
	} else {
		int dec = atoi(operand.c_str());
		string operand_hexa = dectoHex(dec);
		if (operand_hexa.length() == 0) {
			result = result + "00000";
		} else if (operand_hexa.length() == 1) {
			result = result + "0000" + operand_hexa;
		} else if (operand_hexa.length() == 2) {
			result = result + "000" + operand_hexa;
		} else if (operand_hexa.length() == 3) {
			result = result + "00" + operand_hexa;
		} else if (operand_hexa.length() == 4) {
			result = result + "0" + operand_hexa;
		} else if (operand_hexa.length() == 5) {
			result = result + operand_hexa;
		}
	}
	return result;
}

string Check::opCode(string operation, string operand, string address,
		string curaddress) {
	string small_operation = toLowerCase(operation);
	if (small_operation == "rsub") {
		return "4f0000";
	}
	string result = "";
	string op = tables->opTable.at(small_operation).opcode;

	if (tables->opTable.at(small_operation).format == "1") {
		return op;
	} else if (tables->opTable.at(small_operation).format == "2") {
		if (tables->opTable.at(small_operation).operand == "r1") {
			string reg = regFormat(small_operation);
			result = result + op + reg;

			return result;
		} else if (tables->opTable.at(small_operation).operand == "r1,r2") {
			string reg = regFormat2(small_operation);
			result = result + op + reg;
			return result;
		}
	}
	int op_dec = conHexaToDec(op);
	int op_bin = dec_to_binary(op_dec);
	string op_binstr = convertIntToString(op_bin);

	char n = '0';
	char i = '0';
	if (operand[0] == '@') {
		n = '1';
	}
	if (operand[0] == '#') {

		i = '1';
	}
	if (n == '0' && i == '0') {

		n = '1';
		i = '1';
	}

	if (op_binstr.length() == 1) {
		op_binstr = '0' + op_binstr;
	}
	//cout << "totoooo " << op_binstr << endl;
	op_binstr[op_binstr.length() - 1] = i;
	op_binstr[op_binstr.length() - 2] = n;

	int op_binEdit = atoi(op_binstr.c_str());
	int op_decEdit = binary_to_dec(op_binEdit);
	string op_hexEdit = dectoHex(op_decEdit);
	if (op_hexEdit.length() == 1) {
		op_hexEdit = '0' + op_hexEdit;
	}
//cout<<"beto  "<<operation<<"    "<<op_hexEdit<<endl;
	result = result + op_hexEdit;
	if (tables->opTable.at(small_operation).format == "3/4") {
		string xbpe = "";
		bool x = false;
		unsigned int i = 0;
		for (i = 0; i < operand.length(); i++) {
			if (operand[i] == ',') {
				xbpe = "1";
				x = true;
				break;
			}
		}
		if (x == false) {
			xbpe = "0";
		}
		string bp = "";
		string addresse = calcuteAddresse(address, &bp, operand, curaddress);
		if (addresse == "error") {
			return addresse;
		}
		xbpe = xbpe + bp;
		xbpe = xbpe + '0';
//cout<<"beto "<<bp<<"      "<<xbpe<<"    "<<small_operation<<endl;
		int xbpe_bin = atoi(xbpe.c_str());
		int xbpe_dec = binary_to_dec(xbpe_bin);
		string hexa = dectoHex(xbpe_dec);
		if (hexa.length() == 0) {
			hexa = "0";
		}

		result = result + hexa[0] + addresse;
	}

	return result;
}
string Check::calcuteAddresse(string next_a, string *bp, string operand,
		string curaddress) {
	string res = "";
	operand = toLowerCase(operand);
	if (operand[0] == '#' || operand[0] == '@') {
		string tmp = "";
		tmp.assign(operand.begin() + 1, operand.end());
		operand.assign(tmp);
	}
	string tmp = "";
	for (unsigned int i = 0; i < operand.length(); i++) {
		if (operand[i] == ',') {
			break;
		} else {
			tmp = tmp + operand[i];
		}
	}
	operand.assign(tmp);
	if (operand == "*") {
		*bp = "01";
		int nex = conHexaToDec(next_a);
		int cur = conHexaToDec(curaddress);
		int diff = cur - nex;
		string hexa = dectoHex(diff);
		if (hexa.length() == 0) {
			res = "000";
		} else if (hexa.length() == 1) {
			res = "00" + hexa;
		} else if (hexa.length() == 2) {
			res = '0' + hexa;
		} else if (hexa.length() == 3) {
			res = hexa;
		} else {
			res = hexa[hexa.length() - 3];
			res = res + hexa[hexa.length() - 2];
			res = res + hexa[hexa.length() - 1];

		}
		return res;

	}

	int x = tables->symTable.count(operand);
	if (experrsion) {

		int dis_dec = conHexaToDec(adress_expression);
		int next_dec = conHexaToDec(next_a);
		int diff = dis_dec - next_dec;
		//pc condition
		if (diff > -2048 && diff < 2047) {
			*bp = "01";
			string addr = dectoHex(diff);
			if (addr.length() == 0) {
				res = "000";
			} else if (addr.length() == 1) {
				res = "00" + addr;
			} else if (addr.length() == 2) {
				res = '0' + addr;
			} else if (addr.length() == 3) {
				res = addr;
			} else {
				res = addr[addr.length() - 3];
				res = res + addr[addr.length() - 2];
				res = res + addr[addr.length() - 1];

			}
			return res;
		} else {

			return "error";
		}

	} else if (x > 0) {
		string distin = tables->symTable.at(operand);
		int dis_dec = conHexaToDec(distin);
		int next_dec = conHexaToDec(next_a);
		int diff = dis_dec - next_dec;
//cout<<"DIFFF    "<<operand<<"    "<<diff<<endl;
		//pc condition
		if (diff > -2048 && diff < 2047) {

			*bp = "01";
//			cout<<"totooo "<<*bp<<endl;
			string addr = dectoHex(diff);
			if (addr.length() == 0) {
				res = "000";
			} else if (addr.length() == 1) {
				res = "00" + addr;
			} else if (addr.length() == 2) {
				res = '0' + addr;
			} else if (addr.length() == 3) {
				res = addr;
			} else {
				res = addr[addr.length() - 3];
				res = res + addr[addr.length() - 2];
				res = res + addr[addr.length() - 1];

			}
			return res;
		} else {
			//base condition
//
//			int base_dec = conHexaToDec(base);
//			int differ = dis_dec - base_dec;
//			string edit = dectoHex(differ);
//			if (edit.length() == 0) {
//				res = "000";
//			} else if (edit.length() == 1) {
//				res = "00" + edit;
//			} else if (edit.length() == 2) {
//				res = '0' + edit;
//			} else if (edit.length() == 3) {
//				res = edit;
//			}
			return "error";
		}

	} else {
		*bp = "00";
		int decim = atoi(operand.c_str());
		string addr = dectoHex(decim);

		if (addr.length() == 0) {
			res = "000";
		} else if (addr.length() == 1) {
			res = "00" + addr;
		} else if (addr.length() == 2) {

			res = res + '0' + addr;
//			cout << " one   " << res << endl;
		} else {
			res = addr;
		}
		return res;
	}
}
string Check::regFormat(string operand) {
	string reg = "";
	if (operand[0] == 'A') {
		reg = "00";
	} else if (operand[0] == 'X') {
		reg = "10";
	} else if (operand[0] == 'L') {
		reg = "20";
	} else if (operand[0] == 'S') {
		reg = "40";
	} else if (operand[0] == 'T') {
		reg = "50";
	} else if (operand[0] == 'B') {
		reg = "30";
	}
	return reg;
}
string Check::regFormat2(string operand) {
	string reg = "";
	if (operand[0] == 'A' || operand[0] == 'a') {
		reg = '0';
	} else if (operand[0] == 'X' || operand[0] == 'x') {
		reg = '1';
	} else if (operand[0] == 'L' || operand[0] == 'l') {
		reg = '3';
	} else if (operand[0] == 'S' || operand[0] == 's') {
		reg = '4';
	} else if (operand[0] == 'T' || operand[0] == 't') {
		reg = '5';
	} else if (operand[0] == 'B' || operand[0] == 'b') {
		reg = '6';
	}
	if (operand[2] == 'A' || operand[2] == 'a') {
		reg = reg + '0';
	} else if (operand[2] == 'X' || operand[2] == 'x') {
		reg = reg + '1';
	} else if (operand[2] == 'L' || operand[2] == 'l') {
		reg = reg + '3';
	} else if (operand[2] == 'S' || operand[2] == 's') {
		reg = reg + '4';
	} else if (operand[2] == 'T' || operand[2] == 't') {
		reg = reg + '5';
	} else if (operand[2] == 'B' || operand[2] == 'b') {
		reg = reg + '6';
	}
	return reg;
}

string Check::format(string operation, string operand, string address,
		string curaddress, LocCounter loc) {
	string object = "";
	string ob_directive = "";
	adress_expression = "";
	experrsion = false;
	bool directive = checkDirectives(operation, operand, &ob_directive);
	string small_operation = toLowerCase(operation);
	string result = "";
	string op = tables->opTable.at(small_operation).opcode;
	for (unsigned int i = 0; i < operand.length(); i++) {
		if (operand[i] == '+' || operand[i] == '/' || operand[i] == '-'
				|| (operand[i] == '*' && operand.length() != 1)) {
			experrsion = true;
		}
	}
	if (directive == true) {
		return ob_directive;
	} else if (tables->opTable.at(small_operation).format == "1") {
		return op;
	} else if (tables->opTable.at(small_operation).format == "2") {
		if (tables->opTable.at(small_operation).operand == "r1") {
			string reg = regFormat(operand);
			result = result + op + reg;
//			cout<<"totoooo   "<<result<<endl;
			return result;
		} else if (tables->opTable.at(small_operation).operand == "r1,r2") {
			string reg = regFormat2(operand);
			result = result + op + reg;
			return result;
		}
	} else {
		if (experrsion) {
			string excep = "";
			adress_expression = evaluate(operand, loc, &excep);
			if (adress_expression == "error") {
				return "invalid";
			} else {
				if (operation[0] == '+') {
					object = opCodeFor4(operation, operand, address,
							curaddress);
				} else {

					object = opCode(operation, operand, address, curaddress);
				}
			}
			return object;
		} else {
			if (validOperand(operand)) {
				if (operation[0] == '+') {
					object = opCodeFor4(operation, operand, address,
							curaddress);
				} else {

					object = opCode(operation, operand, address, curaddress);
				}
			}
			return object;
		}
	}
	return "non";
}

int Check::conHexaToDec(string s) {
	int y;
	std::stringstream stream;
	stream << s;
	stream >> hex >> y;
	return y;
}
bool Check::isNumberOperand(string st) {
	for (unsigned int i = 0; i < st.length(); i++) {
		if ((st.at(i) >= '0' && st.at(i) <= '9') || st.at(i) == '-'
				|| st.at(i) == '+' || st.at(i) == '/' || st.at(i) == '*') {
			continue;
		} else {
			return false;
		}
	}
	return true;
}
string Check::convertIntToString(int number) {
	ostringstream ostr;
	ostr << number;
	string theNumberString = ostr.str();
	return theNumberString;
}
bool Check::validOperand(string operand) {
	if (operand == "*") {
		return true;
	}

	else if (operand[0] == '#' || operand[0] == '@') {
		string tmp = "";
		tmp.assign(operand.begin() + 1, operand.end());
		operand.assign(tmp);
	}
	bool number = isNumberOperand(operand);
	if (number == true) {
		return true;
	}
	if (number == false) {
		string out_index = "";
		for (unsigned int i = 0; i < operand.length(); i++) {
			if (operand[i] == ',') {
				break;
			} else {
				out_index = out_index + operand[i];
			}
		}

		int found = checkAtHash(out_index);
		if (found == 1) {
			return true;
		}
	}
	return false;
}

string Check::dectoHex(int decimal) {
	std::stringstream stream;
	stream << std::hex << decimal;
	std::string result(stream.str());
	return result;
}

string Check::convDectoHex(int decNum, int r[]) {
	int i = 0;
	string str;
	if (decNum > 0) {
		r[i] = decNum % 16;
		i++;
		decNum = decNum / 16;
		convDectoHex(decNum, r);
	}
	for (int x = (i - 1); x >= 0; --x) {
		if (r[x] > 9) {
			switch (r[x]) {
			case 10: {
				str.append("A");
				break;
			}
			case 11: {
				str.append("B");
				break;
			}
			case 12: {
				str.append("C");
				break;
			}
			case 13: {
				str.append("D");
				break;
			}
			case 14: {
				str.append("E");
				break;
			}
			case 15: {
				str.append("F");
				break;
			}
			}
		} else {
			int a = r[x];
			string s;
			stringstream out;
			out << a;
			s = out.str();
			str.append(s);
		}
	}
	return str;
}

bool Check::checkDirectives(string operation, string operand,
		string *ob_directive) {

	string small_operation = toLowerCase(operation);
	if (small_operation == "start" || small_operation == "end"
			|| small_operation == "org" || small_operation == "equ"
			|| small_operation == "ltorg" || small_operation == "use") {

		*ob_directive = "noObject";
		return true;
	} else if (small_operation == "resb" || small_operation == "resw") {
		*ob_directive = "dir";
		return true;
	}

	else if (small_operation == "word") {

		int operand_dec = atoi(operand.c_str());
		string operand_hexa = dectoHex(operand_dec);
		*ob_directive = operand_hexa;
		return true;
	}

	else if (small_operation == "byte") {
		if (operand[0] == 'x' || operand[0] == 'X') {
			string temp = "";
			for (unsigned int i = 2; i < operand.length() - 1; i++) {
				temp = temp + operand[i];
			}
			*ob_directive = temp;
			return true;
		}

		else if (operand[0] == 'c' || operand[0] == 'C') {
			string temp = "";
			for (unsigned int i = 2; i < operand.length() - 1; i++) {
				int ascii_char = (int) operand[i];
				string hexa_char = dectoHex(ascii_char);
				if (hexa_char.length() == 1) {
					temp = temp + "0" + hexa_char;
				} else {
					temp = temp + hexa_char;
				}
			}
			*ob_directive = temp;
			return true;
		}
	}

	else if (small_operation == "base") {
		// operand field modified
		if (operand[0] == '#' || operand[0] == '@') {
			string tmp = "";
			tmp.assign(operand.begin() + 1, operand.end());
			operand.assign(tmp);
		}
		string tmp = "";
		for (unsigned int i = 0; i < operand.length(); i++) {
			if (operand[i] == ',') {
				break;
			} else {
				tmp = tmp + operand[i];
			}
		}
		operand.assign(tmp);

		string base_address = tables->symTable.at(operand);
		base = base_address;

		*ob_directive = "noObject";
		return true;
	}

	return false;

}

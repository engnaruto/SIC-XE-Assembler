/*
 * Check.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#include "Check.h"

using namespace std;

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

bool Check::checkLabel(string label) {
	bool accep = false;
	int check = checkAtHash(label);

	if (check != 3) {
		if (checkSpaces(label, 1) && isalpha(label[0])) {
			accep = true;
		}

		for (unsigned int i = 1; i < label.length(); i++) {
			if (isalpha(label[i]) && i != label.length() - 1 && accep == true) {
				accep = true;
			} else if (!isalpha(label[i])
					&& ((int) label[i] >= 48 && (int) label[i] <= 57)
					&& i != label.length() - 1 && accep == true) {
				accep = true;

			} else if (label[i] != ' ' && checkSpaces(label, 1)) {
				accep = false;
			}
		}
	} else {
		accep = false;
	}
	return accep;
}

int Check::checkAtHash(string searchable) {
//    map<string, string> symTable;
//    map<string, string> opTable;
//	std::map<std::string, OpInfo> pass1::opTable;
//	std::map<std::string, std::string> pass1::symTable;
	int check1;
	int check2;
	int check = 0;
	int found = 0;
//	symTable.count(searchable);
	if (found > 0) {
		check1 = 1;
		check = 1;
	}
	int found2 = 0;
//	opTable.count(searchable);
	if (found2 > 0) {
		check2 = 2;
		check = 2;
	}
	if (check1 == 1 && check2 == 2) {
		check = 3;
	}
	return check;
}

bool Check::check(string operation) {
	string dir[6];
	dir[0] = "word";
	dir[1] = "byte";
	dir[2] = "resb";
	dir[3] = "resw";
	dir[4] = "start";
	dir[5] = "end";
	map<string, string> big;
	if (operation.empty() == true) {
		return false;
	}
	if (isalpha(operation[0]) == false && operation[0] != '+') {
		return false;
	}
	if (operation[0] == '+') {
		string tmp = "";
		tmp.assign(operation.begin() + 1, operation.end());
		operation.assign(tmp);
	}
	int found = big.count(operation);
	if (found > 0) {
		return true;
	}
	int i;
	for (i = 0; i < 6; i++) {
		if (operation == dir[i]) {
			return true;
		}
	}

	return false;
}

bool Check::checkHexaNumber(string st) {
	for (unsigned int i = 0; i < st.length(); i++) {
		if ((st.at(i) >= '0' && st.at(i) <= '9')
				|| (st.at(i) >= 'a' && st.at(i) <= 'f')) {
			continue;
		} else {
			return false;
		}
	}
	return true;
}
bool Check::checkLabel(string label, map<string, string> labels) {
	if (labels.count(label) > 0) {
		return true;
	} else {
		return false;
	}
}

bool Check::checkLabelAndNubmers(string label, map<string, string> labels) {
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

bool Check::checkRegister(string str1, string str2,
		map<string, string> labels) {
	if (str1 == "a" || str1 == "b" || str1 == "x" || str1 == "t" || str1 == "s"
			|| str1 == "l") {
		if (str2 == "a" || str2 == "b" || str2 == "x" || str2 == "t"
				|| str2 == "s" || str2 == "l") {
			return true;
		} else {
			return false;
		}
	} else {
		if (str2 == "x") //&&checkLabel(str1,labels)==true)
			return true;
		else
			return false;
	}
}

bool Check::checkRegister(string str1) {
	if (str1 == "a" || str1 == "b" || str1 == "x" || str1 == "t" || str1 == "s"
			|| str1 == "l") {
		return true;
	}
	return false;
}

bool Check::checkOperand(string operand, map<string, string> labels) {
	if (operand.at(0) == '\0') {
		return true;
	} else {
		if (operand.at(0) == '#') {
			return checkLabelAndNubmers(operand.substr(1), labels);
		} else if (operand.at(0) == '@') {
			return true; //checkLabel(operand.substr(1),labels);
		} else if (operand.find(",") < 100 && operand.find(",") > 0) {
			int pos = operand.find(",");
			string str1 = operand.substr(0, pos);
			string str2 = operand.substr(pos + 1);
			return checkRegister(str1, str2, labels);

		}
		//one register
		else if (operand.at(1) == ' ' || operand.at(1) == '\0') {
			if (operand.at(0) == 'a' || operand.at(0) == 'b'
					|| operand.at(0) == 'x' || operand.at(0) == 't'
					|| operand.at(0) == 's' || operand.at(0) == 'l') {
				return true;
			} else {
				return false;
			}
		} else {
			return checkLabelAndNubmers(operand, labels);
		}
	}
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


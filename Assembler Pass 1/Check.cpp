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
	int check;
	int found = 0;
//	symTable.count(searchable);
	if (found > 0) {
		check1 = 1;
		check = 1;
	}
	int found2 = 0;
//			opTable.count(searchable);
	if (found2 > 0) {
		check2 = 2;
		check = 2;
	}
	if (check1 == 1 && check2 == 2) {
		check = 3;
	}
	return check;
}

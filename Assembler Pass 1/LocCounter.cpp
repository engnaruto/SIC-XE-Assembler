/*
 * LocCounter.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */
#include <iostream>
#include <iomanip>
#include <sstream>
#include "LocCounter.h"
using namespace std;
LocCounter::LocCounter(string start) {
	hexCounter = start;
	decCounter = conHexaToDec(start);
	makeAddress();
	lineCounter = 1;
	lastLength = 0;
}
LocCounter::~LocCounter() {

}
int LocCounter::getLineCounter() {
	return lineCounter++;
}

int LocCounter::conHexaToDec(string s) {
	int y;
	std::stringstream stream;
	stream << s;
	stream >> hex >> y;
	return y;
}

int i = 0;
void LocCounter::setCounter(std::string strNum) {
	hexCounter = strNum;
	decCounter = conHexaToDec(strNum);
}
void LocCounter::addtoCounter(int addresssize) {
//	decCounter += addresssize;
	hexCounter = dectoHex();
	makeAddress();
	lastLength = addresssize;
}
string LocCounter::getAddress() {
//	makeAddress();
	decCounter += lastLength;
//	hexCounter = dectoHex();
	return hexCounter;
}
string LocCounter::getAddressLabel() {
	return hexCounter;
}

string LocCounter::dectoHex(int num) {
	int r[50];
	i = 0;
	return convDectoHex(num, r);
}
string LocCounter::dectoHex() {
	int r[50];
	i = 0;
	return convDectoHex(decCounter, r);
}
void LocCounter::makeAddress() {
	string s = "";
	for (unsigned int i = 0; i < 5 - hexCounter.length(); i++) {
		s += "0";
	}
	hexCounter = s + hexCounter;
}
string LocCounter::convDectoHex(int decNum, int r[]) {
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

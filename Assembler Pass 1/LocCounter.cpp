/*
 * LocCounter.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */
#include <sstream>
#include "LocCounter.h"
using namespace std;
LocCounter::LocCounter(int start) {
	decCounter = start;
	hexCounter = dectoHex();
}
LocCounter::~LocCounter() {

}
void LocCounter::AddtoCounter(int addresssize) {
	decCounter += addresssize;
	hexCounter = dectoHex();
}
string LocCounter::getHex() {
	return hexCounter;
}

string LocCounter::dectoHex() {
	int r[50];
	i = 0;
	return convDectoHex(decCounter, r);
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

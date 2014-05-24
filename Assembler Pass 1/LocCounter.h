/*
 * LocCounter.h
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#ifndef LOCCOUNTER_H_
#define LOCCOUNTER_H_
#include <iostream>
#include <sstream>
#include <stdlib.h>
class LocCounter {
public:
	LocCounter(std::string start);
	~LocCounter();
	void addtoCounter(int addresssize);
	void setCounter(std::string counter);
	int getLineCounter();
	std::string getAddress();
	std::string getAddressLabel();
	int conHexaToDec(std::string s);
	std::string dectoHex(int num);
	std::string convDectoHex(int decNum, int r[]);
private:
	std::string dectoHex();
	int decCounter;
	int lineCounter;
	std::string hexCounter;
	void makeAddress();
	int lastLength;
//	int i;
};

#endif /* LOCCOUNTER_H_ */

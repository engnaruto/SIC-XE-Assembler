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
	LocCounter(int start);
	~LocCounter();
	void addtoCounter(int addresssize);
	void setCounter(std::string counter);
	int getLineCounter();
	std::string getAddress();
private:
	std::string convDectoHex(int decNum, int r[]);
	std::string dectoHex();
	int decCounter;
	int lineCounter;
	std::string hexCounter;
	void makeAddress();
	int lastLength;
//	int i;
};

#endif /* LOCCOUNTER_H_ */

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
	void AddtoCounter(int addresssize);
	void setCounter(std::string counter);
	int getLineCounter();
	std::string getAddress();
	int decCounter;
	int lineCounter;
	std::string hexCounter;
private:
	std::string convDectoHex(int decNum, int r[]);
	std::string dectoHex();
//	int i;
};

#endif /* LOCCOUNTER_H_ */

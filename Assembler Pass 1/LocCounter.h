/*
 * LocCounter.h
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#ifndef LOCCOUNTER_H_
#define LOCCOUNTER_H_
#include <iostream>
class LocCounter {
public:
	LocCounter(int start);
	~LocCounter();
	void AddtoCounter(int addresssize);
	std::string getHex();
	int decCounter;
	std::string hexCounter;
private:
	std::string convDectoHex();
};

#endif /* LOCCOUNTER_H_ */

/*
 * LocCounter.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#include "LocCounter.h"
using namespace std;
LocCounter::LocCounter(int start) {
	decCounter = start;
	hexCounter = convDectoHex();
}
LocCounter::~LocCounter() {

}
void LocCounter::AddtoCounter(int addresssize) {
	decCounter += addresssize;
	hexCounter = convDectoHex();
}
string LocCounter::getHex() {
	return hexCounter;
}
string LocCounter::convDectoHex() {

}

/*
 * OpInfo.cpp
 *
 *  Created on: May 13, 2014
 *      Author: Naruto
 */

#include "OpInfo.h"
using namespace std;
OpInfo::OpInfo() {

}
OpInfo::OpInfo(std::string operand, std::string format, std::string opcode) {
	this->operand = operand;
	this->opcode = opcode;
	this->format = format;
}
OpInfo::~OpInfo() {

}

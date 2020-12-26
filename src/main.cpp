/*
 * main.cpp
 *
 *  Created on: Nov 23, 2020
 *      Author: theo
 */

#include <iostream>
#include <string>
#include "../include/literal.h"
#include "../include/computer.h"
#include "../include/operator.h"
#include "../include/unaryOperator.h"

using namespace std;

int main(){
	Computer c = Computer::getInstance();
	const string a = "1 1 +";
	c.evalLine(a);
	cout << Stack::getInstance().top()->toString();
}



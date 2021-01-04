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
#include "../include/binaryOperator.h"

using namespace std;


int main(){
	//Stack s = Stack::getInstance();
	creationOperators();
	const shared_ptr<LInteger> l1 = LInteger::makeLiteral(1);
	const shared_ptr<LInteger> l2 = LInteger::makeLiteral(1);
	const shared_ptr<LInteger> l3 = LInteger::makeLiteral(1);

	const shared_ptr<LProgram> l4 = LProgram::makeLiteral("[ 1 + ]");
	Stack::getInstance().push(l1);
	Stack::getInstance().push(l2);
	Stack::getInstance().push(l3);
	Stack::getInstance().push(l4);
	Operator::getInstance().getOperator("IFT").apply(Stack::getInstance());
	const shared_ptr<Literal> l5 = Stack::getInstance().top();
	Literal* litA = l5.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA);
	cout << lIntA->toString();
}

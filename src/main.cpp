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
	const shared_ptr<Literal> l1 = LRational::makeLiteral(19, 5);
	const shared_ptr<Literal> l2 = LReal::makeLiteral(10.0);
	Stack::getInstance().push(l1);
	Stack::getInstance().push(l2);
	Operator::getInstance().getOperator("+").apply(Stack::getInstance());


	const shared_ptr<Literal> l3 = Stack::getInstance().top();
	Literal* litA = l3.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA);
	cout << lIntA->toString();
}

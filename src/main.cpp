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
	cout<<"BLAAAAAAAAAAAAAAAAA \n";
	const shared_ptr<Literal> l1 = LInteger::makeLiteral(19);
	const shared_ptr<Literal> l2 = LInteger::makeLiteral(10);
	Stack::getInstance().push(l1);
	Stack::getInstance().push(l2);

	//Operator o = Operator::getInstance();
	Operator::getInstance().getOperator("+").apply(Stack::getInstance());

	//AddIntInt opp;
	//Not opp = Not::get();
	//opp.apply(Stack::getInstance());
	//AbstractBinaryOperation* f = &opp;
	const shared_ptr<Literal> l3 = Stack::getInstance().top();
	//const shared_ptr<Literal> l3 = f->execution(l1, l2);
	Literal* litA = l3.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA);
	cout << lIntA->getValue();


	/*c.evalLine("1");
	c.evalLine("neg");
	//c.evalLine("not");
	const shared_ptr<Literal> l3 = Stack::getInstance().top();
	Literal* litA = l3.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA);
	cout << lIntA->getValue();*/
}

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

void creationOperators(){
	Clear::get();

	NegInt negInt;
	NegReal negReal;
	NegRational negRational;

	Not::get();

	Dup::get();

	Drop::get();

	AddIntInt addIntInt;
	AddIntReal addIntReal;
	AddRealInt addRealInt;
	AddIntRational addIntRational;
	AddRationalInt addRationalInt;
	AddRationalRational addRationalRational;
	AddRealReal addRealReal;
	AddRealRational addRealRational;
	AddRationalReal addRationalReal;

	MulIntInt mulIntInt;
	MulIntReal mulIntReal;
	MulRealInt mulRealInt;
	MulIntRational mulIntRational;
	MulRationalInt mulRationalInt;
	MulRationalRational mulRationalRational;
	MulRealReal mulRealReal;
	MulRealRational mulRealRational;
	MulRationalReal mulRationalReal;

	SubIntInt subIntInt;
	SubIntReal subIntReal;
	SubRealInt subRealInt;
	SubIntRational subIntRational;
	SubRationalInt subRationalInt;
	SubRationalRational subRationalRational;
	SubRealReal subRealReal;
	SubRealRational subRealRational;
	SubRationalReal subRationalReal;

	DivIntInt divIntInt;
	DivIntReal divIntReal;
	DivRealInt divRealInt;
	DivIntRational divIntRational;
	DivRationalInt divRationalInt;
	DivRationalRational divRationalRational;
	DivRealReal divRealReal;
	DivRealRational divRealRational;
	DivRationalReal divRationalReal;

	ModIntInt modIntInt;

	DivEIntInt diveIntInt;

	EquIntInt equIntInt;
	EquIntReal equIntReal;
	EquRealInt equRealInt;
	EquIntRational equIntRational;
	EquRationalInt equRationalInt;
	EquRationalRational equRationalRational;
	EquRealReal equRealReal;
	EquRealRational equRealRational;
	EquRationalReal equRationalReal;

	DifIntInt difIntInt;
	DifIntReal difIntReal;
	DifRealInt difRealInt;
	DifIntRational difIntRational;
	DifRationalInt difRationalInt;
	DifRationalRational difRationalRational;
	DifRealReal difRealReal;
	DifRealRational difRealRational;
	DifRationalReal difRationalReal;

	InfEquIntInt infEquIntInt;
	InfEquIntReal infEquIntReal;
	InfEquRealInt infEquRealInt;
	InfEquIntRational infEquIntRational;
	InfEquRationalInt infEquRationalInt;
	InfEquRationalRational infEquRationalRational;
	InfEquRealReal infEquRealReal;
	InfEquRealRational infEquRealRational;
	InfEquRationalReal infEquRationalReal;

	InfIntInt infIntInt;
	InfIntReal infIntReal;
	InfRealInt infRealInt;
	InfIntRational infIntRational;
	InfRationalInt infRationalInt;
	InfRationalRational infRationalRational;
	InfRealReal infRealReal;
	InfRealRational infRealRational;
	InfRationalReal infRationalReal;

	SupEquIntInt supEquIntInt;
	SupEquIntReal supEquIntReal;
	SupEquRealInt supEquRealInt;
	SupEquIntRational supEquIntRational;
	SupEquRationalInt supEquRationalInt;
	SupEquRationalRational supEquRationalRational;
	SupEquRealReal supEquRealReal;
	SupEquRealRational supEquRealRational;
	SupEquRationalReal supEquRationalReal;

	SupIntInt supIntInt;
	SupIntReal supIntReal;
	SupRealInt supRealInt;
	SupIntRational supIntRational;
	SupRationalInt supRationalInt;
	SupRationalRational supRationalRational;
	SupRealReal supRealReal;
	SupRealRational supRealRational;
	SupRationalReal supRationalReal;

	And::get();

	Or::get();

	Swap::get();
}

int main(){
	//Stack s = Stack::getInstance();
	creationOperators();
	Computer c = Computer::getInstance();
	const shared_ptr<Literal> l1 = LInteger::makeLiteral(19);
	const shared_ptr<Literal> l2 = LInteger::makeLiteral(10);
	Stack::getInstance().push(l1);
	Stack::getInstance().push(l2);

	//Operator o = Operator::getInstance();
	Operator::getInstance().getOperator("add").apply(Stack::getInstance());

	//AddIntInt opp;
	//Not opp = Not::get();
	//opp.apply(s);
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

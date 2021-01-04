/*
 * ternaryOperator.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */
#include <iostream>
#include <string>
#include <map>

#include "../include/operator.h"
#include "../include/ternaryOperator.h"
#include "../include/computer.h"
#include "../include/literal.h"

using namespace std;

bool TernaryOperator::apply(Stack& s){

	const std::shared_ptr<Literal> elA = s.top();// le premier argument

	const std::shared_ptr<Literal> elB = s.top();// le deuxième

	const std::shared_ptr<Literal> elC = s.top();

    LiteralType A=elA->getType();

    LiteralType B=elB->getType();

    LiteralType C=elC->getType();

    if (possibles.count(make_tuple(A, B, C)) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
    	possibles[make_tuple(A, B, C)]->execution(elA, elB, elC);
    	s.pop();
    	s.pop();
    	s.pop();
    	return true;
    }else{
    	return false;
    }
}

/* Début opérateur Ift */
shared_ptr<Ifte> Ifte::instance = nullptr;

bool Ifte::apply(Stack& s){
	if(s.size() < 3)
		throw OperatorException("Need 3 elements in the stack");
	const shared_ptr<Literal> A = s.top();
	s.pop();
	const shared_ptr<Literal> B = s.top();
	s.pop();
	const shared_ptr<Literal> C = s.top();
	s.pop();
	bool test = true;
	if(C.get()->getType() == linteger){
		Literal* litC = C.get();
		LInteger* lintC = dynamic_cast<LInteger*>(litC);
		if(lintC->getValue()==0)
			test = false;
	}
	if((A.get()->getType() == lprogram || A.get()->getType() == lexpression) && (B.get()->getType() == lprogram || B.get()->getType() == lexpression)){
		if( test ){
			s.push(A);
			Operator::getOperator("EVAL").apply(Stack::getInstance());
			return true;
		}else{
			s.push(B);
			Operator::getOperator("EVAL").apply(Stack::getInstance());
			return true;
		}
	}else{
		s.push(C);
		s.push(B);
		s.push(A);
		throw OperatorException("Need an expression or a program");
	}
}

Ifte& Ifte::get(){
	if(instance == nullptr){
		instance = shared_ptr<Ifte>(new Ifte);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Ifte::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
/* fin opérateur Ift */


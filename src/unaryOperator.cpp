/*
 * unaryOperator.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */
#include <iostream>
#include <string>
#include <map>

#include "../include/operator.h"
#include "../include/unaryOperator.h"
#include "../include/computer.h"
#include "../include/literal.h"

using namespace std;

bool UnaryOperator::apply(Stack& s){

	const shared_ptr<Literal> elA = s.top();// le premier argument
    LiteralType A=elA->getType();
    if (possibles.count(A) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
    	s.pop();
    	const shared_ptr<Literal> res = possibles[A]->execution(elA);
    	s.push(res);
    	return true;
    }else{
    	return false;
    }
}

/* Début opérateur NEG */
shared_ptr<Neg> Neg::instance = nullptr;

Neg& Neg::get(){
	if(instance == nullptr){
		instance = shared_ptr<Neg>(new Neg);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Neg::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

/* Début NegInt */
NegInt::NegInt(){
	Neg::get().addBehaviour(typeA, this);
}
const shared_ptr<Literal> NegInt::execution(const shared_ptr<Literal> A){
	Literal* litA = A.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA);
	int valeur = lIntA->getValue();
	const int newVal = -1 * valeur;
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	//newLit
	return newLit;
}
/* Fin NegInt */
/* Début NegReal */
NegReal::NegReal(){
	Neg::get().addBehaviour(typeA, this);
}
const shared_ptr<Literal> NegReal::execution(const shared_ptr<Literal> A){
	Literal* litA = A.get();
	LReal* lRealA = dynamic_cast<LReal*>(litA);
	const double valeur = lRealA->getValue();
	const double newVal = -1 * valeur;
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	return newLit;
}
/* Fin NegReal */
/* Début NegRational */
NegRational::NegRational(){
	Neg::get().addBehaviour(typeA, this);
}
const shared_ptr<Literal> NegRational::execution(const shared_ptr<Literal> A){
	Literal* litA = A.get();
	LRational* lRationalA = dynamic_cast<LRational*>(litA);
	const int num = lRationalA->getNum();
	const int den = lRationalA->getDen();
	const int newNum = -1 * num;
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, den);
	return newLit;
}
/* Fin NegRational */

/* fin opérateur NEG */


/* Début opérateur Not */
shared_ptr<Not> Not::instance = nullptr;



bool Not::apply(Stack& s){
	const shared_ptr<Literal> A = s.top();
	Literal* litA = A.get();
	if(litA->getType() == linteger){
		LInteger* lIntA = dynamic_cast<LInteger*>(litA);
		int valeur = lIntA->getValue();
		if(valeur == 1){
				const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
				s.push(newLit);
			}
			else{
				const shared_ptr<LInteger> newLit = LInteger::makeLiteral(0);
				s.push(newLit);
			}
	}else{
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
		s.push(newLit);
	}
	return true;
}

Not& Not::get(){
	if(instance == nullptr){
		instance = shared_ptr<Not>(new Not);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Not::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
/* fin opérateur Not */

/* Début Dup */
shared_ptr<Dup> Dup::instance = nullptr;

Dup& Dup::get(){
	if(instance == nullptr){
		instance = shared_ptr<Dup>(new Dup);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Dup::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
bool Dup::apply(Stack& s){

	const shared_ptr<Literal> elA = s.top();
    LiteralType A=elA->getType();
    Literal* litA = elA.get();
    //s.push(Literal::makeLiteral(elA));
    return true;
}
/* Fin Dup */

/* Début Drop */
shared_ptr<Drop> Drop::instance = nullptr;

Drop& Drop::get(){
	if(instance == nullptr){
		instance = shared_ptr<Drop>(new Drop);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Drop::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
bool Drop::apply(Stack& s){
	s.pop();
	return true;
}
/* Fin Drop */

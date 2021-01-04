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

void UnaryOperator::addBehaviour(LiteralType A, std::shared_ptr<AbstractUnaryOperation> a) {
	possibles[A]=a;
}

bool UnaryOperator::apply(Stack& s){
	if(s.size() < 1)
            throw OperatorException("Need 1 element in the stack");
	const shared_ptr<Literal> elA = s.top();
    LiteralType A=elA->getType();


    if (possibles.count(A) > 0) {

    	s.pop();
    	const shared_ptr<Literal> res = possibles[A]->execution(elA);

    	s.push(res);
    	return true;
    }else{
    	return false;
    }
    return false;
}

UnaryOperator::~UnaryOperator(){}

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

void AbstractNeg::addMyself(){
	Neg::get().addBehaviour(this->typeA, shared_from_this());
}



/* Début NegReal */
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
/* Début NegInt */
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
/* fin opérateur NEG */


/* Début opérateur Not */
shared_ptr<Not> Not::instance = nullptr;



bool Not::apply(Stack& s){
	if(s.size() < 1)
            throw OperatorException("Need 1 element in the stack");
	const shared_ptr<Literal> A = s.top();
	s.pop();
	Literal* litA = A.get();
	if(litA->getType() == linteger){
		LInteger* lIntA = dynamic_cast<LInteger*>(litA);
		int valeur = lIntA->getValue();
		if(valeur == 0){
			const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
			s.push(newLit);
		}
		else{
			const shared_ptr<LInteger> newLit = LInteger::makeLiteral(0);
			s.push(newLit);
		}
	}else{
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(0);
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
	if(s.size() < 1)
            throw OperatorException("Need 1 element in the stack");
	const shared_ptr<Literal> elA = s.top();

    const shared_ptr<Literal> newLit = elA->getCopy();
    s.push(newLit);
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

/* Début Eval */
shared_ptr<Eval> Eval::instance = nullptr;

Eval& Eval::get(){
	if(instance == nullptr){
		instance = shared_ptr<Eval>(new Eval);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Eval::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

bool Eval::apply(Stack& s){
    if(s.size() < 1)
        throw OperatorException("Need 1 elements in the stack");
    const shared_ptr<Literal> elA = s.top();
    if (elA->getType() == lexpression){
        s.pop();
        Literal* litA = elA.get();
        LExpression* lexpA = dynamic_cast<LExpression*>(litA);
        const string var = lexpA->getValue();
        Computer::getInstance().pushVariable(var);
    }else if (elA->getType() == lprogram){
        s.pop();
        Literal* litA = elA.get();
        LProgram* lprogA = dynamic_cast<LProgram*>(litA);
        string sProg = lprogA->getValue();
        Computer::getInstance().evalLine(sProg.substr(1, sProg.size()-2));

    }else{
        throw OperatorException("Wesh donne moi une expresiion ou un programme !");
    }
    return true;
}
/* Fin Eval */
/* Début Forget */
shared_ptr<Forget> Forget::instance = nullptr;

Forget& Forget::get(){
	if(instance == nullptr){
		instance = shared_ptr<Forget>(new Forget);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Forget::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
bool Forget::apply(Stack& s){
	const shared_ptr<Literal> elA = s.top();
	if (elA->getType() == lexpression){
		s.pop();
		Literal* litA = elA.get();
		LExpression* lexpA = dynamic_cast<LExpression*>(litA);
		const string var = lexpA->getValue();
		Computer::getInstance().forgetVariable(var);
		return true;
	}else return false;
}
/* Fin Forget */


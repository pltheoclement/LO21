/*
 * unaryOperator.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */
#include <iostream>
#include <string>
#include <map>

#include "../headers/operator.h"
#include "../headers/unaryOperator.h"
#include "../headers/stack.h"
#include "../headers/literal.h"

using namespace std;

void UnaryOperator::apply(Stack& s){

	const shared_ptr<Literal> elA = s.top();// le premier argument
    LiteralType A=elA->getType();
    if (possibles.count(A) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
    	s.pop();
    	possibles[A]->execution(elA);
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
	Neg::get().ajouterComportement(typeA, this);
}
void NegInt::execution(const shared_ptr<Literal> A){
	Literal* litA = A.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA);
	int valeur = lIntA->getValue();
	const int newVal = -1 * valeur;
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	//newLit
	Stack::getInstance().push(newLit);
}
/* Fin NegInt */
/* Début NegReal */
NegReal::NegReal(){
	Neg::get().ajouterComportement(typeA, this);
}
void NegReal::execution(const shared_ptr<Literal> A){
	Literal* litA = A.get();
	LReal* lRealA = dynamic_cast<LReal*>(litA);
	const double valeur = lRealA->getValue();
	const double newVal = -1 * valeur;
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	Stack::getInstance().push(newLit);
}
/* Fin NegReal */
/* Début NegRational */
NegRational::NegRational(){
	Neg::get().ajouterComportement(typeA, this);
}
void NegRational::execution(const shared_ptr<Literal> A){
	Literal* litA = A.get();
	LRational* lRationalA = dynamic_cast<LRational*>(litA);
	const int num = lRationalA->getNum();
	const int den = lRationalA->getDen();
	const int newNum = -1 * num;
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, den);
	Stack::getInstance().push(newLit);
}
/* Fin NegRational */

/* fin opérateur NEG */


/* Début opérateur Not */
shared_ptr<Not> Not::instance = nullptr;

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

/* Début NotInt */
NotInt::NotInt(){
	Not::get().ajouterComportement(typeA, this);
}
void NotInt::execution(const shared_ptr<Literal> A){
	Literal* litA = A.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA);
	int valeur = lIntA->getValue();
	if(valeur == 1){
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
		Stack::getInstance().push(newLit);
	}
	else{
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(0);
		Stack::getInstance().push(newLit);
	}

}
/* Fin NotInt */
/* Début NotReal */
NotReal::NotReal(){
	Not::get().ajouterComportement(typeA, this);
}
void NotReal::execution(const shared_ptr<Literal> A){
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
	Stack::getInstance().push(newLit);
}
/* Fin NotReal */
/* Début NotRational */
NotRational::NotRational(){
	Not::get().ajouterComportement(typeA, this);
}
void NotRational::execution(const shared_ptr<Literal> A){
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
	Stack::getInstance().push(newLit);
}
/* Fin NotRational */
/* Début NotProgram */
NotProgram::NotProgram(){
	Not::get().ajouterComportement(typeA, this);
}
void NotProgram::execution(const shared_ptr<Literal> A){
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
	Stack::getInstance().push(newLit);
}
/* Fin NotProgram */
/* Début NotAtom */
NotAtom::NotAtom(){
	Not::get().ajouterComportement(typeA, this);
}
void NotAtom::execution(const shared_ptr<Literal> A){
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
	Stack::getInstance().push(newLit);
}
/* Fin NotAtom */
/* Début NotExpression */
NotExpression::NotExpression(){
	Not::get().ajouterComportement(typeA, this);
}
void NotExpression::execution(const shared_ptr<Literal> A){
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
	Stack::getInstance().push(newLit);
}
/* Fin NotExpression */

/* fin opérateur Not */

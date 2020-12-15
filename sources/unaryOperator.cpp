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
void NegInt::execution(const shared_ptr<LInteger> A){
	int valeur = A->getValue();
	const int newVal = -1 * valeur;
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	//newLit
	Stack::getInstance().push(newLit);
}
/* Fin NegInt */


/* fin opérateur NEG */


/* Définition de l'opérateur Not */
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

/* fin opérateur Not */

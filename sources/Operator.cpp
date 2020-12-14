/*
 * Operator.cpp
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */
#include <iostream>
#include <string>
#include <map>

#include "../headers/operator.h"
#include "../headers/stack.h"
#include "../headers/literal.h"

using namespace std;

unique_ptr<Operator> Operator::instance = nullptr;

std::map<std::string, shared_ptr<TypeOperator>> Operator::operators = {};

Operator& Operator::getInstance(){
	if(instance == nullptr)
		instance = unique_ptr<Operator>(new Operator);
	return *instance;
}

void Operator::freeInstance(){
	instance = nullptr;
}

bool Operator::isOperator(std::string s){
	return (operators.count(s) > 0);
}

TypeOperator& Operator::getOperator(std::string s){
	return *operators.at(s);
}

void UnaryOperator::apply(Stack& s){

	const std::shared_ptr<Literal> elA = s.top();// le premier argument

    LiteralType A=elA->getType();

    if (possibles.count(A) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
    	possibles[A]->execution(elA);
    	s.pop();
    }
}

void BinaryOperator::apply(Stack& s){

	const std::shared_ptr<Literal> elA = s.top();// le premier argument

	const std::shared_ptr<Literal> elB = s.top();// le deuxième

    LiteralType A=elA->getType();

    LiteralType B=elB->getType();

    if (possibles.count(make_pair(A, B)) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
    	possibles[make_pair(A,B)]->execution(elA, elB);
    	s.pop();
    	s.pop();
    }
}

void TernaryOperator::apply(Stack& s){

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
    }

}

unique_ptr<Add> Add::instance = nullptr;

Add& Add::get(){
	if(instance == nullptr)
		instance = unique_ptr<Add>(new Add);
	return *instance;
}

void Add::free(){
	instance = nullptr;
}

AbstractBinaryOperation::AbstractBinaryOperation(LiteralType litA, LiteralType litB): a(litA), b(litB){
	Add::get().ajouterComportement(a, b, this);
}




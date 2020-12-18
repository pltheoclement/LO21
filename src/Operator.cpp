/*
 * Operator.cpp
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */
#include <iostream>
#include <string>
#include <map>

#include "../include/operator.h"
#include "../include/computer.h"
#include "../include/literal.h"

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

void Operator::addOperator(std::string name, std::shared_ptr<TypeOperator> oper){
	operators.insert(std::make_pair(name, oper));
}

void Operator::delOperator(std::string name){
	if(operators.count(name))
		operators.erase(name);
}

bool Operator::isOperator(std::string s){
	return (operators.count(s) > 0);
}

TypeOperator& Operator::getOperator(std::string s){
	return *operators.at(s);
}

/* Définition de l'opérateur CLEAR */
shared_ptr<Clear> Clear::instance = nullptr;
bool Clear::apply(Stack& s){
	while(s.size() != 0){
		s.pop();
	}
	return true;
}

Clear& Clear::get(){
	if(instance == nullptr){
		instance = shared_ptr<Clear>(new Clear);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Clear::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

/* fin opérateur CLEAR */




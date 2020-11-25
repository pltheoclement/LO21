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

using namespace std;

map<string, Operator*> Operator::operators;

//Operator::operators.insert({"OpAdd", nullptr});

string Operator::isOperator(string s){
	if ( Operator::operators.find(s) != Operator::operators.end())
		return s;
	else
		return "not found";
}

Operator* Operator::getOperator(string s){
	map<string, Operator*>::iterator it;
	it = Operator::operators.find(s);
	if(it == Operator::operators.end())
		throw OperatorException("No operator with this name");
	return it->second;
}



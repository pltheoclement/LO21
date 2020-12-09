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

unique_ptr<Add> Add::instance = nullptr;

Add& Add::get(){
	if(instance == nullptr)
		instance = make_unique<Add>();
	return *instance;
}

void Add::free(){
	instance == nullptr;
}

AbstractBinaryOperation::AbstractBinaryOperation(LiteralType litA, LiteralType litB): a(litA), b(litB){
	Add::get().ajouterComportement(a, b, this);
}


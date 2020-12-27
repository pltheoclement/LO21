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


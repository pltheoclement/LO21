/*
 * concreteBinaryOperator.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */

#include <iostream>
#include <string>
#include <map>

#include "../headers/operator.h"
#include "../headers/binaryOperator.h"
#include "../headers/stack.h"
#include "../headers/literal.h"

using namespace std;

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



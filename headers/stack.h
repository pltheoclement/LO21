/*
 * Stack.h
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */

#ifndef HEADERS_STACK_H_
#define HEADERS_STACK_H_

#include <memory>
#include "literal.h"

using namespace std;
class Stack{
public:
	shared_ptr<Literal> pop();
	void push(shared_ptr<Literal> l);
};


#endif /* HEADERS_STACK_H_ */

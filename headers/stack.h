/*
 * Stack.h
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */

#ifndef HEADERS_STACK_H_
#define HEADERS_STACK_H_

#include "literal.h"

class Stack{
public:
	Literal pop();
	void push(Literal l);
};


#endif /* HEADERS_STACK_H_ */

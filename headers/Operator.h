/*
 * Operator.h
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */

#ifndef HEADERS_OPERATOR_H_
#define HEADERS_OPERATOR_H_

#include <map>
#include <memory>
#include "Stack.h"

using namespace std;

class Operator{
	static map<string, Operator> operators;
	static unique_ptr<Operator> instance = nullptr;

	Operator();
	Operator(const Operator);
	virtual ~Operator();
	void operator=(const Operator);

public :
	static string isOperator(string s);
	static Operator getOperator(string s);
	static Operator getInstance();
	static void freeInstance();
	unsigned int getArity();
	void apply(Stack stack);



};



#endif /* HEADERS_OPERATOR_H_ */

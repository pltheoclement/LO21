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

#include "stack.h"
#include "literal.h"

using namespace std;

class OperatorException {
	string info;
public:
	OperatorException(const string& str): info(str){}
	string getInfo() const { return info; }
};


class Operator{
	static map<string, Operator*> operators;
	unsigned int const arity;


public :
	Operator(unsigned int a) : arity(a){}

	unsigned int getArity(){return arity;}

	static string isOperator(string s);
	static Operator* getOperator(string s);
	virtual ~Operator() = default;

	virtual void apply(Stack &s){
		unique_ptr<Literal> *literals = popLit(s);
		unique_ptr<Literal> result;
		result = operate(literals);
		pushRes(s, result);
	}

	virtual unique_ptr<Literal>* popLit(Stack &s){
		unique_ptr<Literal> *literals = new unique_ptr<Literal>[arity];
		for(int i = 0; i < arity; i++){
			literals[i] = s.pop();
		}
		return literals;
	}

	virtual void pushRes(Stack &s, unique_ptr<Literal> res){
		s.push(*res);
	}
	virtual unique_ptr<Literal> operate(unique_ptr<Literal>* literals) = 0;

};



#endif /* HEADERS_OPERATOR_H_ */

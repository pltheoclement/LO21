/*
 * Operator.h
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */

#ifndef HEADERS_OPERATOR_H_
#define HEADERS_OPERATOR_H_

#include <map>
#include <iostream>
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
	unsigned int const arity;
	static map<string, Operator*> operators;
public :
	Operator(unsigned int a) : arity(a){}
	unsigned int getArity(){return arity;}
	static string isOperator(string s);
	static Operator* getOperator(string s);
	virtual ~Operator() = default;
	virtual void apply(Stack &s){
		shared_ptr<Literal> *literals = popLit(s);
		shared_ptr<Literal> result;
		result = operate(literals);
		pushRes(s, result);
	}
	virtual shared_ptr<Literal>* popLit(Stack &s){
		shared_ptr<Literal> *literals = new shared_ptr<Literal>[arity];
		for(unsigned int i = 0; i < arity; i++){
			literals[i] = s.pop();
		}
		return literals;
	}
	virtual void pushRes(Stack &s, shared_ptr<Literal> res){
		s.push(res);
	}
	virtual shared_ptr<Literal> operate(shared_ptr<Literal>* literals) = 0;
};

class OpAdd: public Operator{
	unsigned int const arity = 2;
public:
	shared_ptr<Literal> operate(shared_ptr<Literal>* literals){
		Literal s;
		s = **literals[0] + **literals[1];
		shared_ptr<Literal> res = make_shared<Literal>(s);
		return res;
	}
};

class OpSub: public Operator{
	unsigned int const arity = 2;
public:
	shared_ptr<Literal> operate(shared_ptr<Literal>* literals){
		Literal s;
		s = **literals[1] - **literals[0];
		shared_ptr<Literal> res = make_shared<Literal>(s);
		return res;
	}
};

class OpMul: public Operator{
	unsigned int const arity = 2;
public:
	shared_ptr<Literal> operate(shared_ptr<Literal>* literals){
		Literal s;
		s = **literals[1] * **literals[0];
		shared_ptr<Literal> res = make_shared<Literal>(s);
		return res;
	}
};

class OpDivE: public Operator{
	unsigned int const arity = 2;
public:
	shared_ptr<Literal> operate(shared_ptr<Literal>* literals){
		Literal s;
		s = **literals[1] / **literals[0];
		shared_ptr<Literal> res = make_shared<Literal>(s);
		return res;
	}
};

class OpDiv: public Operator{
	unsigned int const arity = 2;
public:
	shared_ptr<Literal> operate(shared_ptr<Literal>* literals){
		Literal s;
		LRational l1, l2;
		l1(**literals[1]);
		l2(**literals[0]);
		s = l1 / l2;
		shared_ptr<Literal> res = make_shared<Literal>(s);
		return res;
	}
};



#endif /* HEADERS_OPERATOR_H_ */

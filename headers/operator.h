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

//using namespace std;

class OperatorException {
	std::string info;
public:
	OperatorException(const std::string& str): info(str){}
	std::string getInfo() const { return info; }
};


class AbstractOperation {
};





class TypeOperator {
	std::string name;
public:
	virtual void apply(Stack& s) = 0;
	virtual ~TypeOperator(){};
};

class Clear : public TypeOperator {
	std::string name = "clear";
	static std::shared_ptr<Clear> instance;
	Clear() = default;
public:
	void apply(Stack& s);
	static Clear& get();
	static void free();
};





class Operator{
	static std::map<std::string, std::shared_ptr<TypeOperator>> operators;
	static std::unique_ptr<Operator> instance;
	Operator() = default;

public:
	static bool isOperator(std::string s);
	static TypeOperator& getOperator(std::string s);
	static void addOperator(std::string name, std::shared_ptr<TypeOperator> o);
	static void delOperator(std::string name);
	static Operator& getInstance();
	static void freeInstance();

};

#endif /* HEADERS_OPERATOR_H_ */

/*
 * Operator.h
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */

#ifndef HEADERS_UNARYOPERATOR_H_
#define HEADERS_UNARYOPERATOR_H_

#include <map>
#include <iostream>
#include <memory>

#include "computer.h"
#include "literal.h"
#include "operator.h"

class AbstractUnaryOperation : public AbstractOperation, public std::enable_shared_from_this<AbstractUnaryOperation> {
protected:
	LiteralType typeA;
public:
	//AbstractUnaryOperation() = default;
	AbstractUnaryOperation(LiteralType a) : typeA(a){}
	virtual const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A) = 0;
	virtual ~AbstractUnaryOperation() = default;
};

class AbstractNeg : public AbstractUnaryOperation{
public:
	AbstractNeg() = default;
	~AbstractNeg() = default;
	AbstractNeg(LiteralType a):AbstractUnaryOperation(a){}
	void addMyself() override;
};

class NegInt : public AbstractNeg{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
	NegInt(): AbstractNeg(linteger){}
};

class NegReal : public AbstractNeg{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
	NegReal(): AbstractNeg(lreal){}
};

class NegRational : public AbstractNeg{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
	NegRational(): AbstractNeg(lrational){}
};

class UnaryOperator : public TypeOperator{
protected:
	std::map<LiteralType, std::shared_ptr<AbstractUnaryOperation>> possibles;
public :
    virtual ~UnaryOperator();
    UnaryOperator(){};
    void addBehaviour(LiteralType A, std::shared_ptr<AbstractUnaryOperation> a);
    bool apply(Stack& s);
};

class Neg : public UnaryOperator {
protected:
	std::string name = "NEG";
	static std::shared_ptr<Neg> instance;
	Neg() = default;
public:
	static Neg& get();
	static void free();
};


class Not : public UnaryOperator {
protected:
	std::string name = "NOT";
	static std::shared_ptr<Not> instance;
	Not() = default;
public:
	static Not& get();
	static void free();
	bool apply(Stack& s);
};

class Eval : public UnaryOperator {
protected:
	std::string name = "EVAL";
	static std::shared_ptr<Eval> instance;
	Eval() = default;
public:
	static Eval& get();
	static void free();
	bool apply(Stack& s);

};

class Dup : public UnaryOperator {
protected:
	std::string name = "DUP";
	static std::shared_ptr<Dup> instance;
	Dup() = default;
public:
	static Dup& get();
	static void free();
	bool apply(Stack& s);
};

class Drop : public UnaryOperator {
protected:
	std::string name = "DROP";
	static std::shared_ptr<Drop> instance;
	Drop() = default;
public:
	static Drop& get();
	static void free();
	bool apply(Stack& s);
};

class Forget : public UnaryOperator {
protected:
	std::string name = "FORGET";
	static std::shared_ptr<Forget> instance;
	Forget() = default;
public:
	static Forget& get();
	static void free();
	bool apply(Stack& s);
};

#endif

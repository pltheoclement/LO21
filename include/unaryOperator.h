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
	AbstractUnaryOperation() = default;
	virtual const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A) = 0;
	virtual ~AbstractUnaryOperation() = default;
	virtual void addMyself() = 0;
};

class AbstractNeg : public AbstractUnaryOperation{
public:
	AbstractNeg() = default;
	~AbstractNeg() = default;
	void addMyself() override;
};

class NegInt : public AbstractNeg{
protected:
	LiteralType typeA = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
	~NegInt(){std::cout<<"Chui plus la";}
};

class NegReal : public AbstractNeg{
protected:
	LiteralType typeA = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
};

class NegRational : public AbstractNeg{
protected:
	LiteralType typeA = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
};

class UnaryOperator : public TypeOperator{
	std::map<LiteralType, std::shared_ptr<AbstractUnaryOperation>> possibles;
public :
    virtual ~UnaryOperator();
    UnaryOperator(){};
    void addBehaviour(LiteralType A, std::shared_ptr<AbstractUnaryOperation> a);
    bool apply(Stack& s);
};

class Neg : public UnaryOperator {
	std::string name = "NEG";
	static std::shared_ptr<Neg> instance;
	Neg() = default;
public:
	static Neg& get();
	static void free();
};


class Not : public UnaryOperator {
	std::string name = "NOT";
	static std::shared_ptr<Not> instance;
	Not() = default;
public:
	static Not& get();
	static void free();
	bool apply(Stack& s);
};

class Eval : public UnaryOperator {
	std::string name = "EVAL";
	static std::shared_ptr<Eval> instance;
	Eval() = default;
public:
	static Eval& get();
	static void free();
	bool apply(Stack& s);

};

class Dup : public UnaryOperator {
	std::string name = "DUP";
	static std::shared_ptr<Dup> instance;
	Dup() = default;
public:
	static Dup& get();
	static void free();
	bool apply(Stack& s);
};

class Drop : public UnaryOperator {
	std::string name = "DROP";
	static std::shared_ptr<Drop> instance;
	Drop() = default;
public:
	static Drop& get();
	static void free();
	bool apply(Stack& s);
};

#endif

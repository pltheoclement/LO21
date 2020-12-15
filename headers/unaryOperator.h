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

#include "stack.h"
#include "literal.h"
#include "operator.h"

class AbstractUnaryOperation : public AbstractOperation {
	LiteralType typeA;
public:
	AbstractUnaryOperation() = default;
	virtual void execution(const std::shared_ptr<Literal> A) = 0;
	virtual ~AbstractUnaryOperation() = default;
};

class AbstractNeg : public AbstractUnaryOperation{
public:
	AbstractNeg() = default;
	~AbstractNeg() = default;
};

class NegInt : public AbstractNeg{
	LiteralType typeA = linteger;
public:
	NegInt();
	void execution(const std::shared_ptr<Literal> A);
};

class NegReal : public AbstractNeg{
	LiteralType typeA = lreal;
public:
	NegReal();
	void execution(const std::shared_ptr<Literal> A);
};

class NegRational : public AbstractNeg{
	LiteralType typeA = lrational;
public:
	NegRational();
	void execution(const std::shared_ptr<Literal> A);
};


class AbstractNot : public AbstractUnaryOperation{
public:
	AbstractNot() = default;
	~AbstractNot() = default;
};

class NotInt : public AbstractNot{
	LiteralType typeA = linteger;
public:
	NotInt();
	void execution(const std::shared_ptr<Literal> A);
};

class NotReal : public AbstractNot{
	LiteralType typeA = lreal;
public:
	NotReal();
	void execution(const std::shared_ptr<Literal> A);
};

class NotRational : public AbstractNot{
	LiteralType typeA = lrational;
public:
	NotRational();
	void execution(const std::shared_ptr<Literal> A);
};

class NotProgram : public AbstractNot{
	LiteralType typeA = lprogram;
public:
	NotProgram();
	void execution(const std::shared_ptr<Literal> A);
};

class NotAtom : public AbstractNot{
	LiteralType typeA = latom;
public:
	NotAtom();
	void execution(const std::shared_ptr<Literal> A);
};

class NotExpression : public AbstractNot{
	LiteralType typeA = lexpression;
public:
	NotExpression();
	void execution(const std::shared_ptr<Literal> A);
};

class UnaryOperator : public TypeOperator{
	std::map<LiteralType, AbstractUnaryOperation*> possibles;
public :
    virtual ~UnaryOperator(){};
    UnaryOperator(){};
    void ajouterComportement(LiteralType A, AbstractUnaryOperation* a) { possibles[A]=a; }
    void apply(Stack& s);
};

class Neg : public UnaryOperator {
	std::string name = "neg";
	static std::shared_ptr<Neg> instance;
	Neg() = default;
public:
	static Neg& get();
	static void free();
};

class Not : public UnaryOperator {
	std::string name = "not";
	static std::shared_ptr<Not> instance;
	Not() = default;
public:
	static Not& get();
	static void free();
};

class Eval : public UnaryOperator {
	std::string name = "eval";
	static std::shared_ptr<Eval> instance;
	Eval() = default;
public:
	static Eval& get();
	static void free();
};

class Dup : public UnaryOperator {
	std::string name = "dup";
	static std::shared_ptr<Dup> instance;
	Dup() = default;
public:
	static Dup& get();
	static void free();
};

class Drop : public UnaryOperator {
	std::string name = "drop";
	static std::shared_ptr<Drop> instance;
	Drop() = default;
public:
	static Drop& get();
	static void free();
};


class Swap : public UnaryOperator {
	std::string name = "swap";
	static std::shared_ptr<Swap> instance;
	Swap() = default;
public:
	static Swap& get();
	static void free();
};

#endif

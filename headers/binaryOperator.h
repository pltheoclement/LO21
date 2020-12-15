/*
 * binaryOperator.h
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */

#ifndef HEADERS_BINARYOPERATOR_H_
#define HEADERS_BINARYOPERATOR_H_

#include <map>
#include <iostream>
#include <memory>

#include "stack.h"
#include "literal.h"
#include "operator.h"


class AbstractBinaryOperation : public AbstractOperation {
	LiteralType a;
	LiteralType b;
public:
	AbstractBinaryOperation(LiteralType litA, LiteralType litB);
	virtual void execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B) = 0;
	virtual ~AbstractBinaryOperation() = default;
};

class AbstractAdd : public AbstractBinaryOperation{
};

class AbstractMul : public AbstractBinaryOperation{
};

class AbstractDiv : public AbstractBinaryOperation{
};


class AddIntInt : public AbstractAdd {
public:
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};

class AddIntReal : public AbstractAdd {
public:
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};

class MulIntInt : public AbstractMul {
public:
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};

class MulRealInt : public AbstractMul {
public:
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};

class DivRealInt : public AbstractDiv {
public:
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};


class BinaryOperator : public TypeOperator{
    std::map<std::pair<LiteralType,LiteralType>, AbstractBinaryOperation*> possibles;

public :
    virtual ~BinaryOperator(){};
    BinaryOperator(){};
    void ajouterComportement(LiteralType A, LiteralType B, AbstractBinaryOperation* a) { possibles[std::make_pair(A,B)]=a; }
    void apply(Stack& s);
};

class Add : public BinaryOperator {
	std::string name = "add";
	static std::shared_ptr<Add> instance;
	Add() = default;
public:
	static Add& get();
	static void free();
};

class Mul : public BinaryOperator {
	std::string name = "mul";
	static std::shared_ptr<Mul> instance;
public:
	static Mul& get();
	static void free();
};

class Div : public BinaryOperator {
	std::string name = "div";
	static std::shared_ptr<Div> instance;
public:
	static Div& get();
	static void free();
};

class DivE : public BinaryOperator {
	std::string name = "dive";
	static std::shared_ptr<DivE> instance;
public:
	static DivE& get();
	static void free();
};

class Sub : public BinaryOperator {
	std::string name = "sub";
	static std::shared_ptr<Sub> instance;
public:
	static Sub& get();
	static void free();
};

class Equ : public BinaryOperator {
	std::string name = "equ";
	static std::shared_ptr<Equ> instance;
public:
	static Equ& get();
	static void free();
};

class Dif : public BinaryOperator {
	std::string name = "dif";
	static std::shared_ptr<Dif> instance;
public:
	static Dif& get();
	static void free();
};

class InfEqu : public BinaryOperator {
	std::string name = "InfEqu";
	static std::shared_ptr<InfEqu> instance;
public:
	static InfEqu& get();
	static void free();
};

class Inf : public BinaryOperator {
	std::string name = "Inf";
	static std::shared_ptr<Inf> instance;
public:
	static Inf& get();
	static void free();
};

class SupEqu : public BinaryOperator {
	std::string name = "SupEqu";
	static std::shared_ptr<SupEqu> instance;
public:
	static SupEqu& get();
	static void free();
};

class Sup : public BinaryOperator {
	std::string name = "Sup";
	static std::shared_ptr<Sup> instance;
public:
	static Sup& get();
	static void free();
};

class And : public BinaryOperator {
	std::string name = "and";
	static std::shared_ptr<And> instance;
public:
	static And& get();
	static void free();
};

class Or : public BinaryOperator {
	std::string name = "or";
	static std::shared_ptr<Or> instance;
public:
	static Or& get();
	static void free();
};

class Ift : public BinaryOperator {
	std::string name = "ift";
	static std::shared_ptr<Ift> instance;
public:
	static Ift& get();
	static void free();
};



#endif /* HEADERS_BINARYOPERATOR_H_ */

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


class AbstractOperation {
};

class AbstractUnaryOperation : public AbstractOperation {
	LiteralType a;
public:
	AbstractUnaryOperation(LiteralType litA);
	virtual const std::shared_ptr<Literal> execution(std::shared_ptr<Literal> A) = 0;
	virtual ~AbstractUnaryOperation() = default;
};

class AbstractTernaryOperation : public AbstractOperation {
	LiteralType a;
	LiteralType b;
	LiteralType c;
public:
	AbstractTernaryOperation(LiteralType litA, LiteralType litB, LiteralType litC);
	virtual const std::shared_ptr<Literal> execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B, std::shared_ptr<Literal> C) = 0;
	virtual ~AbstractTernaryOperation() = default;
};

class AbstractBinaryOperation : public AbstractOperation {
	LiteralType a;
	LiteralType b;
public:
	AbstractBinaryOperation(LiteralType litA, LiteralType litB);
	virtual const std::shared_ptr<Literal> execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B) = 0;
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
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};

class AddIntReal : public AbstractAdd {
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};

class MulIntInt : public AbstractMul {
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};

class MulRealInt : public AbstractMul {
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};

class DivRealInt : public AbstractDiv {
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	}
};




class TypeOperator {
	std::string name;
public:
	virtual void apply(Stack& s) = 0;
	virtual ~TypeOperator(){};
};

class Clear : public TypeOperator {
	std::string name = "clear";
	static std::unique_ptr<Clear> instance;
	Clear() = default;
public:
	static Clear& get();
	static void free();
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
	static std::unique_ptr<Neg> instance;
	Neg() = default;
public:
	static Neg& get();
	static void free();
};

class Not : public UnaryOperator {
	std::string name = "not";
	static std::unique_ptr<Not> instance;
	Not() = default;
public:
	static Not& get();
	static void free();
};

class Eval : public UnaryOperator {
	std::string name = "eval";
	static std::unique_ptr<Eval> instance;
	Eval() = default;
public:
	static Eval& get();
	static void free();
};

class Dup : public UnaryOperator {
	std::string name = "dup";
	static std::unique_ptr<Dup> instance;
	Dup() = default;
public:
	static Dup& get();
	static void free();
};

class Drop : public UnaryOperator {
	std::string name = "drop";
	static std::unique_ptr<Drop> instance;
	Drop() = default;
public:
	static Drop& get();
	static void free();
};

class BinaryOperator : public TypeOperator{
    std::map<pair<LiteralType,LiteralType>, AbstractBinaryOperation*> possibles;

public :
    virtual ~BinaryOperator(){};
    BinaryOperator(){};
    void ajouterComportement(LiteralType A, LiteralType B, AbstractBinaryOperation* a) { possibles[make_pair(A,B)]=a; }
    void apply(Stack& s);
};

class Add : public BinaryOperator {
	std::string name = "add";
	static std::unique_ptr<Add> instance;
	Add() = default;
public:
	static Add& get();
	static void free();
};

class Mul : public BinaryOperator {
	std::string name = "mul";
	static std::unique_ptr<Mul> instance;
public:
	static Mul& get();
	static void free();
};

class Div : public BinaryOperator {
	std::string name = "div";
	static std::unique_ptr<Div> instance;
public:
	static Div& get();
	static void free();
};

class Sub : public BinaryOperator {
	std::string name = "sub";
	static std::unique_ptr<Sub> instance;
public:
	static Sub& get();
	static void free();
};

class Equ : public BinaryOperator {
	std::string name = "equ";
	static std::unique_ptr<Equ> instance;
public:
	static Equ& get();
	static void free();
};

class Dif : public BinaryOperator {
	std::string name = "dif";
	static std::unique_ptr<Dif> instance;
public:
	static Dif& get();
	static void free();
};

class InfEqu : public BinaryOperator {
	std::string name = "InfEqu";
	static std::unique_ptr<InfEqu> instance;
public:
	static InfEqu& get();
	static void free();
};

class Inf : public BinaryOperator {
	std::string name = "Inf";
	static std::unique_ptr<Inf> instance;
public:
	static Inf& get();
	static void free();
};

class SupEqu : public BinaryOperator {
	std::string name = "SupEqu";
	static std::unique_ptr<SupEqu> instance;
public:
	static SupEqu& get();
	static void free();
};

class Sup : public BinaryOperator {
	std::string name = "Sup";
	static std::unique_ptr<Sup> instance;
public:
	static Sup& get();
	static void free();
};

class And : public BinaryOperator {
	std::string name = "and";
	static std::unique_ptr<And> instance;
public:
	static And& get();
	static void free();
};

class Or : public BinaryOperator {
	std::string name = "or";
	static std::unique_ptr<Or> instance;
public:
	static Or& get();
	static void free();
};

class Ift : public BinaryOperator {
	std::string name = "ift";
	static std::unique_ptr<Ift> instance;
public:
	static Ift& get();
	static void free();
};

class Swap : public UnaryOperator {
	std::string name = "swap";
	static std::unique_ptr<Swap> instance;
	Swap() = default;
public:
	static Swap& get();
	static void free();
};


class TernaryOperator : public TypeOperator{
    std::map<tuple<LiteralType,LiteralType, LiteralType>, AbstractTernaryOperation*> possibles;

public :
    virtual ~TernaryOperator(){}
    TernaryOperator(){}
    void ajouterComportement(LiteralType A, LiteralType B, LiteralType C, AbstractTernaryOperation* a) { possibles[make_tuple(A, B, C)]=a; }
    void apply(Stack& s);
};


class Operator{
	static std::map<std::string, shared_ptr<TypeOperator>> operators;
	static std::unique_ptr<Operator> instance;
	Operator() = default;

public:
	static bool isOperator(std::string s);
	static TypeOperator& getOperator(std::string s);
	static Operator& getInstance();
	static void freeInstance();

};

#endif /* HEADERS_OPERATOR_H_ */

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
protected:
	LiteralType typeA;
	LiteralType typeB;
public:
	AbstractBinaryOperation(){}
	virtual void execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B) = 0;
	virtual ~AbstractBinaryOperation() = default;
};


class BinaryOperator : public TypeOperator{
    std::map<std::pair<LiteralType,LiteralType>, AbstractBinaryOperation*> possibles;

public :
    virtual ~BinaryOperator(){};
    BinaryOperator(){};
    void addBehaviour(LiteralType A, LiteralType B, AbstractBinaryOperation* a) { possibles[std::make_pair(A,B)]=a; }
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

class AbstractAdd : public AbstractBinaryOperation{
public:
	AbstractAdd() = default;
	~AbstractAdd() = default;
};

class AddIntInt : public AbstractAdd{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	AddIntInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntReal : public AbstractAdd{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	AddIntReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealInt : public AddIntReal{
public:
	AddRealInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntRational : public AbstractAdd{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	AddIntRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalInt : public AddIntRational{
public:
	AddRationalInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalRational : public AbstractAdd{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	AddRationalRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealReal : public AbstractAdd{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	AddRealReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealRational : public AbstractAdd{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	AddRealRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalReal : public AddRealRational{
public:
	AddRationalReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};






class Mul : public BinaryOperator {
	std::string name = "mul";
	static std::shared_ptr<Mul> instance;
	Mul() = default;
public:
	static Mul& get();
	static void free();
};

class AbstractMul : public AbstractBinaryOperation{
public:
	AbstractMul() = default;
	~AbstractMul() = default;
};

class MulIntInt : public AbstractMul{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	MulIntInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntReal : public AbstractMul{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	MulIntReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealInt : public MulIntReal{
public:
	MulRealInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntRational : public AbstractMul{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	MulIntRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalInt : public MulIntRational{
public:
	MulRationalInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalRational : public AbstractMul{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	MulRationalRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealReal : public AbstractMul{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	MulRealReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealRational : public AbstractMul{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	MulRealRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalReal : public MulRealRational{
public:
	MulRationalReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class Sub : public BinaryOperator {
	std::string name = "sub";
	static std::shared_ptr<Sub> instance;
	Sub() = default;
public:
	static Sub& get();
	static void free();
};

class AbstractSub : public AbstractBinaryOperation{
public:
	AbstractSub() = default;
	~AbstractSub() = default;
};

class SubIntInt : public AbstractSub{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	SubIntInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntReal : public AbstractSub{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	SubIntReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealInt : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	SubRealInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntRational : public AbstractSub{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	SubIntRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalInt : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	SubRationalInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalRational : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	SubRationalRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealReal : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	SubRealReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealRational : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	SubRealRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalReal : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	SubRationalReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Div : public BinaryOperator {
	std::string name = "div";
	static std::shared_ptr<Div> instance;
	Div() = default;
public:
	static Div& get();
	static void free();
};

class AbstractDiv : public AbstractBinaryOperation{
public:
	AbstractDiv() = default;
	~AbstractDiv() = default;
};

class DivIntInt : public AbstractDiv{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	DivIntInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntReal : public AbstractDiv{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	DivIntReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealInt : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	DivRealInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntRational : public AbstractDiv{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	DivIntRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalInt : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	DivRationalInt();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalRational : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	DivRationalRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealReal : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	DivRealReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealRational : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	DivRealRational();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalReal : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	DivRationalReal();
	void execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};



class DivE : public BinaryOperator {
	std::string name = "dive";
	static std::shared_ptr<DivE> instance;
public:
	static DivE& get();
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

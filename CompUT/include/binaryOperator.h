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

#include "computer.h"
#include "literal.h"
#include "operator.h"


class AbstractBinaryOperation : public AbstractOperation, public std::enable_shared_from_this<AbstractBinaryOperation> {
protected:
	LiteralType typeA;
	LiteralType typeB;
public:
	AbstractBinaryOperation() = default;
	AbstractBinaryOperation(LiteralType a, LiteralType b) : typeA(a), typeB(b){}
	virtual const std::shared_ptr<Literal> execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B) = 0;
	virtual ~AbstractBinaryOperation() = default;
	virtual void addMyself() = 0;
};


class BinaryOperator : public TypeOperator{
protected:
    std::map<std::pair<LiteralType,LiteralType>, std::shared_ptr<AbstractBinaryOperation>> possibles;

public :
    virtual ~BinaryOperator(){};
    BinaryOperator(){};
    void addBehaviour(LiteralType A, LiteralType B, std::shared_ptr<AbstractBinaryOperation> a);
    bool apply(Stack& s);
};

class Add : public BinaryOperator {
protected:
	std::string name = "+";
	static std::shared_ptr<Add> instance;
	Add() = default;
public:
	static Add& get();
	static void free();
};

class AbstractAdd : public AbstractBinaryOperation{
public:
	AbstractAdd() = default;
	AbstractAdd(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	~AbstractAdd() = default;
	void addMyself() override;
};

class AddIntInt : public AbstractAdd{
public:
	AddIntInt(): AbstractAdd(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntReal : public AbstractAdd{
public:
	AddIntReal(): AbstractAdd(linteger, lreal){}
	AddIntReal(LiteralType a, LiteralType b):AbstractAdd(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealInt : public AddIntReal{
public:
	AddRealInt(): AddIntReal(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntRational : public AbstractAdd{
public:
	AddIntRational(): AbstractAdd(linteger, lrational){}
	AddIntRational(LiteralType a, LiteralType b):AbstractAdd(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalInt : public AddIntRational{
public:
	AddRationalInt(): AddIntRational(lrational, linteger){}

	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalRational : public AbstractAdd{
public:
	AddRationalRational(): AbstractAdd(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealReal : public AbstractAdd{
public:
	AddRealReal(): AbstractAdd(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealRational : public AbstractAdd{
public:
	AddRealRational(): AbstractAdd(lreal, lrational){}
	AddRealRational(LiteralType a, LiteralType b):AbstractAdd(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalReal : public AddRealRational{
public:
	AddRationalReal(): AddRealRational(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};






class Mul : public BinaryOperator {
protected:
	std::string name = "*";
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
	AbstractMul(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class MulIntInt : public AbstractMul{
public:
	MulIntInt(): AbstractMul(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntReal : public AbstractMul{
public:
	MulIntReal(): AbstractMul(linteger, lreal){}
	MulIntReal(LiteralType a, LiteralType b):AbstractMul(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealInt : public MulIntReal{
public:
	MulRealInt(): MulIntReal(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntRational : public AbstractMul{
public:
	MulIntRational(): AbstractMul(linteger, lrational){}
	MulIntRational(LiteralType a, LiteralType b):AbstractMul(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalInt : public MulIntRational{
public:
	MulRationalInt(): MulIntRational(lrational, linteger){}

	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalRational : public AbstractMul{
public:
	MulRationalRational(): AbstractMul(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealReal : public AbstractMul{
public:
	MulRealReal(): AbstractMul(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealRational : public AbstractMul{
public:
	MulRealRational(): AbstractMul(lreal, lrational){}
	MulRealRational(LiteralType a, LiteralType b):AbstractMul(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalReal : public MulRealRational{
public:
	MulRationalReal(): MulRealRational(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class Sub : public BinaryOperator {
protected:
	std::string name = "-";
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
	AbstractSub(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class SubIntInt : public AbstractSub{
public:
	SubIntInt(): AbstractSub(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntReal : public AbstractSub{
public:
	SubIntReal(): AbstractSub(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealInt : public AbstractSub{
public:
	SubRealInt(): AbstractSub(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntRational : public AbstractSub{
public:
	SubIntRational(): AbstractSub(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalInt : public AbstractSub{
public:
	SubRationalInt(): AbstractSub(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalRational : public AbstractSub{
public:
	SubRationalRational(): AbstractSub(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealReal : public AbstractSub{
public:
	SubRealReal(): AbstractSub(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealRational : public AbstractSub{
public:
	SubRealRational(): AbstractSub(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalReal : public AbstractSub{
public:
	SubRationalReal(): AbstractSub(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Div : public BinaryOperator {
protected:
	std::string name = "/";
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
	AbstractDiv(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class DivIntInt : public AbstractDiv{
public:
	DivIntInt(): AbstractDiv(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntReal : public AbstractDiv{
public:
	DivIntReal(): AbstractDiv(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealInt : public AbstractDiv{
public:
	DivRealInt(): AbstractDiv(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntRational : public AbstractDiv{
public:
	DivIntRational(): AbstractDiv(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalInt : public AbstractDiv{
public:
	DivRationalInt(): AbstractDiv(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalRational : public AbstractDiv{
public:
	DivRationalRational(): AbstractDiv(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealReal : public AbstractDiv{
public:
	DivRealReal(): AbstractDiv(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealRational : public AbstractDiv{
public:
	DivRealRational(): AbstractDiv(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalReal : public AbstractDiv{
public:
	DivRationalReal(): AbstractDiv(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Mod : public BinaryOperator {
protected:
	std::string name = "MOD";
	static std::shared_ptr<Mod> instance;
	Mod() = default;
public:
	static Mod& get();
	static void free();
};

class AbstractMod : public AbstractBinaryOperation{
public:
	AbstractMod() = default;
	~AbstractMod() = default;
	AbstractMod(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class ModIntInt : public AbstractMod{
public:
	ModIntInt(): AbstractMod(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivE : public BinaryOperator {
protected:
	std::string name = "DIV";
	static std::shared_ptr<DivE> instance;
	DivE() = default;
public:
	static DivE& get();
	static void free();
};

class AbstarctDivE : public AbstractBinaryOperation{
public:
	AbstarctDivE() = default;
	~AbstarctDivE() = default;
	AbstarctDivE(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class DivEIntInt : public AbstarctDivE{
public:
	DivEIntInt(): AbstarctDivE(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Equ : public BinaryOperator {
protected:
	std::string name = "=";
	static std::shared_ptr<Equ> instance;
	Equ() = default;
public:
	static Equ& get();
	static void free();
};

class AbstractEqu : public AbstractBinaryOperation{
public:
	AbstractEqu() = default;
	~AbstractEqu() = default;
	AbstractEqu(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class EquIntInt : public AbstractEqu{
public:
	EquIntInt(): AbstractEqu(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquIntReal : public AbstractEqu{
public:
	EquIntReal(): AbstractEqu(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealInt : public AbstractEqu{
public:
	EquRealInt(): AbstractEqu(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquIntRational : public AbstractEqu{
public:
	EquIntRational(): AbstractEqu(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalInt : public AbstractEqu{
public:
	EquRationalInt(): AbstractEqu(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalRational : public AbstractEqu{
public:
	EquRationalRational(): AbstractEqu(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealReal : public AbstractEqu{
public:
	EquRealReal(): AbstractEqu(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealRational : public AbstractEqu{
public:
	EquRealRational(): AbstractEqu(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalReal : public AbstractEqu{
public:
	EquRationalReal(): AbstractEqu(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class Dif : public BinaryOperator {
protected:
	std::string name = "!=";
	static std::shared_ptr<Dif> instance;
	Dif() = default;
public:
	static Dif& get();
	static void free();
};

class AbstractDif : public AbstractBinaryOperation{
public:
	AbstractDif() = default;
	~AbstractDif() = default;
	AbstractDif(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class DifIntInt : public AbstractDif{
public:
	DifIntInt(): AbstractDif(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifIntReal : public AbstractDif{
public:
	DifIntReal(): AbstractDif(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealInt : public AbstractDif{
public:
	DifRealInt(): AbstractDif(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifIntRational : public AbstractDif{
public:
	DifIntRational(): AbstractDif(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalInt : public AbstractDif{
public:
	DifRationalInt(): AbstractDif(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalRational : public AbstractDif{
public:
	DifRationalRational(): AbstractDif(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealReal : public AbstractDif{
public:
	DifRealReal(): AbstractDif(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealRational : public AbstractDif{
public:
	DifRealRational(): AbstractDif(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalReal : public AbstractDif{
public:
	DifRationalReal(): AbstractDif(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class InfEqu : public BinaryOperator {
protected:
	std::string name = "=<";
	static std::shared_ptr<InfEqu> instance;
	InfEqu() = default;
public:
	static InfEqu& get();
	static void free();
};

class AbstractInfEqu : public AbstractBinaryOperation{
public:
	AbstractInfEqu() = default;
	~AbstractInfEqu() = default;
	AbstractInfEqu(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class InfEquIntInt : public AbstractInfEqu{
public:
	InfEquIntInt(): AbstractInfEqu(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquIntReal : public AbstractInfEqu{
public:
	InfEquIntReal(): AbstractInfEqu(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealInt : public AbstractInfEqu{
public:
	InfEquRealInt(): AbstractInfEqu(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquIntRational : public AbstractInfEqu{
public:
	InfEquIntRational(): AbstractInfEqu(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalInt : public AbstractInfEqu{
public:
	InfEquRationalInt(): AbstractInfEqu(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalRational : public AbstractInfEqu{
public:
	InfEquRationalRational(): AbstractInfEqu(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealReal : public AbstractInfEqu{
public:
	InfEquRealReal(): AbstractInfEqu(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealRational : public AbstractInfEqu{
public:
	InfEquRealRational(): AbstractInfEqu(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalReal : public AbstractInfEqu{
public:
	InfEquRationalReal(): AbstractInfEqu(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Inf : public BinaryOperator {
protected:
	std::string name = "<";
	static std::shared_ptr<Inf> instance;
	Inf() = default;
public:
	static Inf& get();
	static void free();
};

class AbstractInf : public AbstractBinaryOperation{
public:
	AbstractInf() = default;
	AbstractInf(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	~AbstractInf() = default;
	void addMyself() override;
};

class InfIntInt : public AbstractInf{
public:
	InfIntInt(): AbstractInf(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfIntReal : public AbstractInf{
public:
	InfIntReal(): AbstractInf(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealInt : public AbstractInf{
public:
	InfRealInt(): AbstractInf(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfIntRational : public AbstractInf{
public:
	InfIntRational(): AbstractInf(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalInt : public AbstractInf{
public:
	InfRationalInt(): AbstractInf(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalRational : public AbstractInf{
public:
	InfRationalRational(): AbstractInf(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealReal : public AbstractInf{
public:
	InfRealReal(): AbstractInf(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealRational : public AbstractInf{
public:
	InfRealRational(): AbstractInf(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalReal : public AbstractInf{
public:
	InfRationalReal(): AbstractInf(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEqu : public BinaryOperator {
protected:
	std::string name = ">=";
	static std::shared_ptr<SupEqu> instance;
	SupEqu() = default;
public:
	static SupEqu& get();
	static void free();
};

class AbstractSupEqu : public AbstractBinaryOperation{
public:
	AbstractSupEqu() = default;
	~AbstractSupEqu() = default;
	AbstractSupEqu(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class SupEquIntInt : public AbstractSupEqu{
public:
	SupEquIntInt(): AbstractSupEqu(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquIntReal : public AbstractSupEqu{
public:
	SupEquIntReal(): AbstractSupEqu(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealInt : public AbstractSupEqu{
public:
	SupEquRealInt(): AbstractSupEqu(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquIntRational : public AbstractSupEqu{
public:
	SupEquIntRational(): AbstractSupEqu(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalInt : public AbstractSupEqu{
public:
	SupEquRationalInt(): AbstractSupEqu(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalRational : public AbstractSupEqu{
public:
	SupEquRationalRational(): AbstractSupEqu(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealReal : public AbstractSupEqu{
public:
	SupEquRealReal(): AbstractSupEqu(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealRational : public AbstractSupEqu{
public:
	SupEquRealRational(): AbstractSupEqu(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalReal : public AbstractSupEqu{
public:
	SupEquRationalReal(): AbstractSupEqu(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Sup : public BinaryOperator {
protected:
	std::string name = ">";
	static std::shared_ptr<Sup> instance;
	Sup() = default;
public:
	static Sup& get();
	static void free();
};

class AbstractSup : public AbstractBinaryOperation{
public:
	AbstractSup() = default;
	~AbstractSup() = default;
	AbstractSup(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class SupIntInt : public AbstractSup{
public:
	SupIntInt(): AbstractSup(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupIntReal : public AbstractSup{
public:
	SupIntReal(): AbstractSup(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealInt : public AbstractSup{
public:
	SupRealInt(): AbstractSup(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupIntRational : public AbstractSup{
public:
	SupIntRational(): AbstractSup(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalInt : public AbstractSup{
public:
	SupRationalInt(): AbstractSup(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalRational : public AbstractSup{
public:
	SupRationalRational(): AbstractSup(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealReal : public AbstractSup{
public:
	SupRealReal(): AbstractSup(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealRational : public AbstractSup{
public:
	SupRealRational(): AbstractSup(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalReal : public AbstractSup{
public:
	SupRationalReal(): AbstractSup(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class And : public BinaryOperator {
protected:
	std::string name = "AND";
	static std::shared_ptr<And> instance;
	And() = default;
public:
	static And& get();
	static void free();
	bool apply(Stack& s);
};

class Or : public BinaryOperator {
protected:
	std::string name = "OR";
	static std::shared_ptr<Or> instance;
	Or() = default;
public:
	static Or& get();
	static void free();
	bool apply(Stack& s);
};

class Swap : public BinaryOperator {
protected:
	std::string name = "SWAP";
	static std::shared_ptr<Swap> instance;
	Swap() = default;
public:
	static Swap& get();
	static void free();
	bool apply(Stack& s);
};

#endif /* HEADERS_BINARYOPERATOR_H_ */

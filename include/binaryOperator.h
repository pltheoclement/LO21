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


class AbstractBinaryOperation : public AbstractOperation {
protected:
	LiteralType typeA;
	LiteralType typeB;
public:
	AbstractBinaryOperation(){}
	virtual const std::shared_ptr<Literal> execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B) = 0;
	virtual ~AbstractBinaryOperation() = default;
};


class BinaryOperator : public TypeOperator{
    std::map<std::pair<LiteralType,LiteralType>, AbstractBinaryOperation*> possibles;

public :
    virtual ~BinaryOperator(){};
    BinaryOperator(){};
    void addBehaviour(LiteralType A, LiteralType B, AbstractBinaryOperation* a) { possibles[std::make_pair(A,B)]=a; }
    bool apply(Stack& s);
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
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntReal : public AbstractAdd{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	AddIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealInt : public AddIntReal{
public:
	AddRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntRational : public AbstractAdd{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	AddIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalInt : public AddIntRational{
public:
	AddRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalRational : public AbstractAdd{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	AddRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealReal : public AbstractAdd{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	AddRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealRational : public AbstractAdd{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	AddRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalReal : public AddRealRational{
public:
	AddRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
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
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntReal : public AbstractMul{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	MulIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealInt : public MulIntReal{
public:
	MulRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntRational : public AbstractMul{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	MulIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalInt : public MulIntRational{
public:
	MulRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalRational : public AbstractMul{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	MulRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealReal : public AbstractMul{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	MulRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealRational : public AbstractMul{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	MulRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalReal : public MulRealRational{
public:
	MulRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
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
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntReal : public AbstractSub{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	SubIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealInt : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	SubRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntRational : public AbstractSub{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	SubIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalInt : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	SubRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalRational : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	SubRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealReal : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	SubRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealRational : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	SubRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalReal : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	SubRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
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
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntReal : public AbstractDiv{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	DivIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealInt : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	DivRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntRational : public AbstractDiv{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	DivIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalInt : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	DivRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalRational : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	DivRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealReal : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	DivRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealRational : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	DivRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalReal : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	DivRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Mod : public BinaryOperator {
	std::string name = "mod";
	static std::shared_ptr<Mod> instance;
	Mod() = default;
public:
	static Mod& get();
	static void free();
};

class AbstarctMod : public AbstractBinaryOperation{
public:
	AbstarctMod() = default;
	~AbstarctMod() = default;
};

class ModIntInt : public AbstarctMod{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	ModIntInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivE : public BinaryOperator {
	std::string name = "DivE";
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
};

class DivEIntInt : public AbstarctDivE{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	DivEIntInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Equ : public BinaryOperator {
	std::string name = "Equ";
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
};

class EquIntInt : public AbstractEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	EquIntInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquIntReal : public AbstractEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	EquIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealInt : public AbstractEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	EquRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquIntRational : public AbstractEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	EquIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalInt : public AbstractEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	EquRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalRational : public AbstractEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	EquRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealReal : public AbstractEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	EquRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealRational : public AbstractEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	EquRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalReal : public AbstractEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	EquRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class Dif : public BinaryOperator {
	std::string name = "Dif";
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
};

class DifIntInt : public AbstractDif{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	DifIntInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifIntReal : public AbstractDif{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	DifIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealInt : public AbstractDif{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	DifRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifIntRational : public AbstractDif{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	DifIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalInt : public AbstractDif{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	DifRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalRational : public AbstractDif{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	DifRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealReal : public AbstractDif{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	DifRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealRational : public AbstractDif{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	DifRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalReal : public AbstractDif{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	DifRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class InfEqu : public BinaryOperator {
	std::string name = "InfEqu";
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
};

class InfEquIntInt : public AbstractInfEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	InfEquIntInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquIntReal : public AbstractInfEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	InfEquIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealInt : public AbstractInfEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	InfEquRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquIntRational : public AbstractInfEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	InfEquIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalInt : public AbstractInfEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	InfEquRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalRational : public AbstractInfEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	InfEquRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealReal : public AbstractInfEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	InfEquRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealRational : public AbstractInfEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	InfEquRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalReal : public AbstractInfEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	InfEquRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Inf : public BinaryOperator {
	std::string name = "Inf";
	static std::shared_ptr<Inf> instance;
	Inf() = default;
public:
	static Inf& get();
	static void free();
};

class AbstractInf : public AbstractBinaryOperation{
public:
	AbstractInf() = default;
	~AbstractInf() = default;
};

class InfIntInt : public AbstractInf{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	InfIntInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfIntReal : public AbstractInf{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	InfIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealInt : public AbstractInf{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	InfRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfIntRational : public AbstractInf{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	InfIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalInt : public AbstractInf{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	InfRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalRational : public AbstractInf{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	InfRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealReal : public AbstractInf{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	InfRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealRational : public AbstractInf{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	InfRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalReal : public AbstractInf{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	InfRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEqu : public BinaryOperator {
	std::string name = "SupEqu";
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
};

class SupEquIntInt : public AbstractSupEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	SupEquIntInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquIntReal : public AbstractSupEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	SupEquIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealInt : public AbstractSupEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	SupEquRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquIntRational : public AbstractSupEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	SupEquIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalInt : public AbstractSupEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	SupEquRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalRational : public AbstractSupEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	SupEquRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealReal : public AbstractSupEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	SupEquRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealRational : public AbstractSupEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	SupEquRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalReal : public AbstractSupEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	SupEquRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Sup : public BinaryOperator {
	std::string name = "Sup";
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
};

class SupIntInt : public AbstractSup{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	SupIntInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupIntReal : public AbstractSup{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	SupIntReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealInt : public AbstractSup{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	SupRealInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupIntRational : public AbstractSup{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	SupIntRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalInt : public AbstractSup{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	SupRationalInt();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalRational : public AbstractSup{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	SupRationalRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealReal : public AbstractSup{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	SupRealReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealRational : public AbstractSup{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	SupRealRational();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalReal : public AbstractSup{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	SupRationalReal();
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class And : public BinaryOperator {
	std::string name = "And";
	static std::shared_ptr<And> instance;
	And() = default;
public:
	static And& get();
	static void free();
	bool apply(Stack& s);
};

class Or : public BinaryOperator {
	std::string name = "Or";
	static std::shared_ptr<Or> instance;
	Or() = default;
public:
	static Or& get();
	static void free();
	bool apply(Stack& s);
};

class Swap : public BinaryOperator {
	std::string name = "Swap";
	static std::shared_ptr<Or> instance;
	Swap() = default;
public:
	static Swap& get();
	static void free();
	bool apply(Stack& s);
};

#endif /* HEADERS_BINARYOPERATOR_H_ */

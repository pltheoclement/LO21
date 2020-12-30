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
	AbstractBinaryOperation(){}
	virtual const std::shared_ptr<Literal> execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B) = 0;
	virtual ~AbstractBinaryOperation() = default;
	virtual void addMyself() = 0;
};


class BinaryOperator : public TypeOperator{
    std::map<std::pair<LiteralType,LiteralType>, std::shared_ptr<AbstractBinaryOperation>> possibles;

public :
    virtual ~BinaryOperator(){};
    BinaryOperator(){};
    void addBehaviour(LiteralType A, LiteralType B, std::shared_ptr<AbstractBinaryOperation> a);
    bool apply(Stack& s);
};

class Add : public BinaryOperator {
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
	~AbstractAdd() = default;
	void addMyself() override;
};

class AddIntInt : public AbstractAdd{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	AddIntInt() = default;
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntReal : public AbstractAdd{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealInt : public AddIntReal{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntRational : public AbstractAdd{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalInt : public AddIntRational{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalRational : public AbstractAdd{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealReal : public AbstractAdd{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealRational : public AbstractAdd{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalReal : public AddRealRational{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};






class Mul : public BinaryOperator {
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
	void addMyself() override;
};

class MulIntInt : public AbstractMul{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntReal : public AbstractMul{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealInt : public MulIntReal{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntRational : public AbstractMul{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalInt : public MulIntRational{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalRational : public AbstractMul{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealReal : public AbstractMul{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealRational : public AbstractMul{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalReal : public MulRealRational{
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class Sub : public BinaryOperator {
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
	void addMyself() override;
};

class SubIntInt : public AbstractSub{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntReal : public AbstractSub{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealInt : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntRational : public AbstractSub{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalInt : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalRational : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealReal : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealRational : public AbstractSub{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalReal : public AbstractSub{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Div : public BinaryOperator {
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
	void addMyself() override;
};

class DivIntInt : public AbstractDiv{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntReal : public AbstractDiv{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealInt : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntRational : public AbstractDiv{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalInt : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalRational : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealReal : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealRational : public AbstractDiv{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalReal : public AbstractDiv{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Mod : public BinaryOperator {
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
	void addMyself() override;
};

class ModIntInt : public AbstractMod{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivE : public BinaryOperator {
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
	void addMyself() override;
};

class DivEIntInt : public AbstarctDivE{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Equ : public BinaryOperator {
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
	void addMyself() override;
};

class EquIntInt : public AbstractEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquIntReal : public AbstractEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealInt : public AbstractEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquIntRational : public AbstractEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalInt : public AbstractEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalRational : public AbstractEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealReal : public AbstractEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealRational : public AbstractEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalReal : public AbstractEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class Dif : public BinaryOperator {
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
	void addMyself() override;
};

class DifIntInt : public AbstractDif{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifIntReal : public AbstractDif{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealInt : public AbstractDif{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifIntRational : public AbstractDif{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalInt : public AbstractDif{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalRational : public AbstractDif{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealReal : public AbstractDif{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealRational : public AbstractDif{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalReal : public AbstractDif{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};


class InfEqu : public BinaryOperator {
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
	void addMyself() override;
};

class InfEquIntInt : public AbstractInfEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquIntReal : public AbstractInfEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealInt : public AbstractInfEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquIntRational : public AbstractInfEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalInt : public AbstractInfEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalRational : public AbstractInfEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealReal : public AbstractInfEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealRational : public AbstractInfEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalReal : public AbstractInfEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Inf : public BinaryOperator {
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
	~AbstractInf() = default;
	void addMyself() override;
};

class InfIntInt : public AbstractInf{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfIntReal : public AbstractInf{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealInt : public AbstractInf{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfIntRational : public AbstractInf{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalInt : public AbstractInf{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalRational : public AbstractInf{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealReal : public AbstractInf{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealRational : public AbstractInf{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalReal : public AbstractInf{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEqu : public BinaryOperator {
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
	void addMyself() override;
};

class SupEquIntInt : public AbstractSupEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquIntReal : public AbstractSupEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealInt : public AbstractSupEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquIntRational : public AbstractSupEqu{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalInt : public AbstractSupEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalRational : public AbstractSupEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealReal : public AbstractSupEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealRational : public AbstractSupEqu{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalReal : public AbstractSupEqu{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class Sup : public BinaryOperator {
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
	void addMyself() override;
};

class SupIntInt : public AbstractSup{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupIntReal : public AbstractSup{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealInt : public AbstractSup{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupIntRational : public AbstractSup{
protected:
	LiteralType typeA = linteger;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalInt : public AbstractSup{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = linteger;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalRational : public AbstractSup{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealReal : public AbstractSup{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealRational : public AbstractSup{
protected:
	LiteralType typeA = lreal;
	LiteralType typeB = lrational;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalReal : public AbstractSup{
protected:
	LiteralType typeA = lrational;
	LiteralType typeB = lreal;
public:
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class And : public BinaryOperator {
	std::string name = "AND";
	static std::shared_ptr<And> instance;
	And() = default;
public:
	static And& get();
	static void free();
	bool apply(Stack& s);
};

class Or : public BinaryOperator {
	std::string name = "OR";
	static std::shared_ptr<Or> instance;
	Or() = default;
public:
	static Or& get();
	static void free();
	bool apply(Stack& s);
};

class Swap : public BinaryOperator {
	std::string name = "SWAP";
	static std::shared_ptr<Swap> instance;
	Swap() = default;
public:
	static Swap& get();
	static void free();
	bool apply(Stack& s);
};

#endif /* HEADERS_BINARYOPERATOR_H_ */

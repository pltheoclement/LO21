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

class AbstractTernaryOperation : public AbstractOperation {
	LiteralType a;
	LiteralType b;
	LiteralType c;
public:
	AbstractTernaryOperation(LiteralType litA, LiteralType litB, LiteralType litC);
	virtual Literal* execution(Literal* A, Literal* B, Literal* C) = 0;
	virtual ~AbstractTernaryOperation() = default;
};

class AbstractBinaryOperation : public AbstractOperation {
	LiteralType a;
	LiteralType b;
public:
	AbstractBinaryOperation(LiteralType litA, LiteralType litB);
	virtual Literal* execution(Literal* A, Literal* B) = 0;
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
	Literal* execution(Literal* A, Literal* B){
		LInteger* ret = new LInteger(1);
		return ret;
	}
};

class AddIntReal : public AbstractAdd {
public:
	Literal* execution(Literal* A, Literal* B){
		LInteger* ret = new LInteger(1);
		return ret;
	}
};

class MulIntInt : public AbstractMul {
public:
	Literal* execution(Literal* A, Literal* B){
		LInteger* ret = new LInteger(1);
		return ret;
	}
};

class MulRealInt : public AbstractMul {
public:
	Literal* execution(Literal* A, Literal* B){
		LInteger* ret = new LInteger(1);
		return ret;
	}
};

class DivRealInt : public AbstractDiv {
public:
	Literal* execution(Literal* A, Literal* B){
		LInteger* ret = new LInteger(1);
		return ret;
	}
};

class Operator {
	std::string name;
public:
	virtual void execute() = 0;
	virtual ~Operator(){};
};

class BinaryOperator : public Operator{
    std::map<pair<LiteralType,LiteralType>, AbstractBinaryOperation*> possibles;


public :
    virtual ~BinaryOperator(){};
    BinaryOperator(){};
    void ajouterComportement(LiteralType A, LiteralType B, AbstractBinaryOperation* a) { possibles[make_pair(A,B)]=a; }

    void execute() {

    	Literal* elA;// le premier argument

    	Literal* elB;// le deuxième

        LiteralType A=elA->getType();

        LiteralType B=elB->getType();

        if (possibles.count(make_pair(A, B)) > 0) // existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
        	possibles[make_pair(A,B)]->execution(elA, elB);
        else
        	throw OperatorException("erreur");//sinon gestion de l'erreur
    }
};

class Add : public BinaryOperator {
	std::string name = "add";
	static std::unique_ptr<Add> instance;
public:
	static Add& get();
	static void free();
	~Add(){};
};

class Mul : public BinaryOperator {
	std::string name = "mul";
	static std::unique_ptr<Mul> instance;
public:
	static Add& get();
	static void free();
};

class Div : public BinaryOperator {
	std::string name = "div";
	static std::unique_ptr<Div> instance;
public:
	static Add& get();
	static void free();
};

class TernaryOperator : public Operator{
    std::map<tuple<LiteralType,LiteralType, LiteralType>, AbstractBinaryOperation*> possibles;
    //~BinaryOperator();
    //BinaryOperator();

public :
    void ajouterComportement(LiteralType A, LiteralType B, LiteralType C,AbstractBinaryOperation* a) { possibles[make_tuple(A,B, C)]=a; }

    void execute() {

    	Literal* elA;// le premier argument

    	Literal* elB;// le deuxième

    	Literal* elC;// le deuxième

        LiteralType A=elA->getType();

        LiteralType B=elB->getType();

        LiteralType C=elC->getType();

        if (possibles.count(std::make_tuple(A, B, C)) > 0) // existe bien dans ta map then possibles[make_tuple(A,B)].execution(); // @suppress("Method cannot be resolved")
        	possibles[make_tuple(A,B, C)]->execution(elA, elB);
        else
        	throw OperatorException("erreur");//sinon gestion de l'erreur
    }
};
#endif /* HEADERS_OPERATOR_H_ */

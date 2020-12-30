/*
 * concreteBinaryOperator.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */

#include <iostream>
#include <string>
#include <map>

#include "../include/operator.h"
#include "../include/binaryOperator.h"
#include "../include/computer.h"
#include "../include/literal.h"

using namespace std;


void BinaryOperator::addBehaviour(LiteralType A, LiteralType B, shared_ptr<AbstractBinaryOperation> a) {
	possibles[std::make_pair(A,B)]=a;
}

bool BinaryOperator::apply(Stack& s){

	const std::shared_ptr<Literal> elA = s.top();// le premier argument
	s.pop();

	const std::shared_ptr<Literal> elB = s.top();// le deuxième
	s.pop();

    LiteralType A=elA->getType();

    LiteralType B=elB->getType();
    if (possibles.count(make_pair(A, B)) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
    	cout << "coucou";
    	cout.flush();
    	auto opp = possibles.at(make_pair(A,B));
    	const shared_ptr<Literal> res = opp->execution(elA, elB);
    	s.push(res);
    	return true;
    }else{
    	s.push(elB);
    	s.push(elA);
    	return false;
    }
}

void AbstractAdd::addMyself(){
	Add::get().addBehaviour(typeA, typeB, shared_from_this());
}

/* Début Add */
shared_ptr<Add> Add::instance = nullptr;

Add& Add::get(){
	if(instance == nullptr){
		instance = shared_ptr<Add>(new Add);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Add::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

/* Début AddIntInt */

const std::shared_ptr<Literal> AddIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin AddIntInt */
/* Début AddIntReal */

const std::shared_ptr<Literal> AddIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
	const double newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin AddIntReal */
/* Début AddRealInt */

const std::shared_ptr<Literal> AddRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return (AddIntReal::execution(B, A));
}
/* Fin AddRealInt */
/* Début AddIntRational */

const std::shared_ptr<Literal> AddIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
	const int newNum = valeurA * valeurBden + valeurBnum; //On effectue l'opération Add
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurBden); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin AddIntRational */
/* Début AddRationalInt */

const std::shared_ptr<Literal> AddRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return AddIntRational::execution(B, A);
}
/* Fin AddRationalInt */
/* Début AddRationalRational */
const std::shared_ptr<Literal> AddRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
	const int newNum = valeurAnum * valeurBden + valeurBnum * valeurAden; //On effectue l'opération Add
	const int newDen = valeurBden * valeurAden;
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, newDen); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin AddRationalRational */
/* Début AddRealReal */

const std::shared_ptr<Literal> AddRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
	const double newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin AddRealReal */
/* Début AddRealRational */

const std::shared_ptr<Literal> AddRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
	const double newVal = valeurA + (valeurBnum / valeurBden); //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin AddRealRational */
/* Début AddRationalReal */

const std::shared_ptr<Literal> AddRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return AddRealRational::execution(B, A);
}
/* Fin AddRationalReal */
/* Fin Add */


/* Début Mul */
shared_ptr<Mul> Mul::instance = nullptr;

Mul& Mul::get(){
	if(instance == nullptr){
		instance = shared_ptr<Mul>(new Mul);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Mul::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractMul::addMyself(){
	Mul::get().addBehaviour(typeA, typeB, shared_from_this());
}

/* Début MulIntInt */

const std::shared_ptr<Literal> MulIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurA * valeurB; //On effectue l'opération Mul
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin MulIntInt */
/* Début MulIntReal */

const std::shared_ptr<Literal> MulIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
	const double newVal = valeurA * valeurB; //On effectue l'opération Mul
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin MulIntReal */
/* Début MulRealInt */

const std::shared_ptr<Literal> MulRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return MulIntReal::execution(B, A);
}
/* Fin MulRealInt */
/* Début MulIntRational */

const std::shared_ptr<Literal> MulIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
	const int newNum = valeurA * valeurBnum; //On effectue l'opération Mul
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurBden); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin MulIntRational */
/* Début MulRationalInt */

const std::shared_ptr<Literal> MulRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return MulIntRational::execution(B, A);
}
/* Fin MulRationalInt */
/* Début MulRationalRational */

const std::shared_ptr<Literal> MulRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
	const int newNum = valeurAnum * valeurBnum; //On effectue l'opération Mul
	const int newDen = valeurBden * valeurAden;
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, newDen); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin MulRationalRational */
/* Début MulRealReal */

const std::shared_ptr<Literal> MulRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
	const double newVal = valeurA * valeurB; //On effectue l'opération Mul
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin MulRealReal */
/* Début MulRealRational */

const std::shared_ptr<Literal> MulRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
	const double newVal = valeurA * (valeurBnum / valeurBden); //On effectue l'opération Mul
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin MulRealRational */
/* Début MulRationalReal */

const std::shared_ptr<Literal> MulRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return MulRealRational::execution(B, A);
}
/* Fin MulRationalReal */
/* Fin Mul */

/* Début Sub */
shared_ptr<Sub> Sub::instance = nullptr;

Sub& Sub::get(){
	if(instance == nullptr){
		instance = shared_ptr<Sub>(new Sub);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Sub::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractSub::addMyself(){
	Sub::get().addBehaviour(typeA, typeB, shared_from_this());
}

/* Début SubIntInt */

const std::shared_ptr<Literal> SubIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB - valeurA; //On effectue l'opération Sub
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SubIntInt */
/* Début SubIntReal */

const std::shared_ptr<Literal> SubIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
	const double newVal = valeurB - valeurA; //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SubIntReal */
/* Début SubRealInt */

const std::shared_ptr<Literal> SubRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* ldoubleA = dynamic_cast<LReal*>(litA); //On cast ce pointeur en LInteger
	LInteger* lintB = dynamic_cast<LInteger*>(litB);
	double valeurA = ldoubleA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lintB->getValue();
	const double newVal = valeurB - valeurA; //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}

/* Fin SubRealInt */
/* Début SubIntRational */

const std::shared_ptr<Literal> SubIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
	const int newNum = valeurBnum - (valeurA * valeurBden); //On effectue l'opération Sub
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurBden); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SubIntRational */
/* Début SubRationalInt */

const std::shared_ptr<Literal> SubRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurB = lIntB->getValue(); //On récupère la valeur de ce Literal
	int valeurAnum = lRatA->getNum();
	int valeurAden = lRatA->getDen();
	const int newNum = (valeurB * valeurAden) - valeurAnum; //On effectue l'opération Sub
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurAden); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SubRationalInt */
/* Début SubRationalRational */

const std::shared_ptr<Literal> SubRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
	const int newNum = valeurAden * valeurBnum - valeurAnum * valeurBden; //On effectue l'opération Sub
	const int newDen = valeurBden * valeurAden;
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, newDen); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SubRationalRational */
/* Début SubRealReal */

const std::shared_ptr<Literal> SubRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
	const double newVal = valeurB - valeurA; //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SubRealReal */
/* Début SubRealRational */

const std::shared_ptr<Literal> SubRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
	const double newVal = (valeurBnum / valeurBden) - valeurA; //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SubRealRational */
/* Début SubRationalReal */

const std::shared_ptr<Literal> SubRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce podoubleeur en LReal
	LReal* lRealB = dynamic_cast<LReal*>(litB);
	double valeurB = lRealB->getValue(); //On récupère la valeur de ce Literal
	double valeurAnum = lRatA->getNum();
	double valeurAden = lRatA->getDen();
	const double newVal = valeurB - (valeurAnum / valeurAden); //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SubRationalReal */
/* Fin Sub */

/* Début Div */
shared_ptr<Div> Div::instance = nullptr;

Div& Div::get(){
	if(instance == nullptr){
		instance = shared_ptr<Div>(new Div);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Div::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractDiv::addMyself(){
	Div::get().addBehaviour(typeA, typeB, shared_from_this());
}

/* Début DivIntInt */

const std::shared_ptr<Literal> DivIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
	const int newVal = valeurB / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivIntInt */
/* Début DivIntReal */

const std::shared_ptr<Literal> DivIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
	const double newVal = valeurB / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivIntReal */
/* Début DivRealInt */

const std::shared_ptr<Literal> DivRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* ldoubleA = dynamic_cast<LReal*>(litA); //On cast ce pointeur en LInteger
	LInteger* lintB = dynamic_cast<LInteger*>(litB);
	double valeurA = ldoubleA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lintB->getValue();
	const double newVal = valeurB / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}

/* Fin DivRealInt */
/* Début DivIntRational */

const std::shared_ptr<Literal> DivIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
	const int newNum = (valeurBden * valeurA); //On effectue l'opération Div
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurBnum); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivIntRational */
/* Début DivRationalInt */

const std::shared_ptr<Literal> DivRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurB = lIntB->getValue(); //On récupère la valeur de ce Literal
	int valeurAnum = lRatA->getNum();
	int valeurAden = lRatA->getDen();
	const int newNum = (valeurB * valeurAden); //On effectue l'opération Div
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurAnum); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivRationalInt */
/* Début DivRationalRational */

const std::shared_ptr<Literal> DivRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
	const int newNum = valeurAnum * valeurBden; //On effectue l'opération Div
	const int newDen = valeurBnum * valeurAden;
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, newDen); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivRationalRational */
/* Début DivRealReal */

const std::shared_ptr<Literal> DivRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
	const double newVal = valeurB / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivRealReal */
/* Début DivRealRational */

const std::shared_ptr<Literal> DivRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
	const double newVal = (valeurBnum / valeurBden) / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivRealRational */
/* Début DivRationalReal */

const std::shared_ptr<Literal> DivRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce podoubleeur en LReal
	LReal* lRealB = dynamic_cast<LReal*>(litB);
	double valeurB = lRealB->getValue(); //On récupère la valeur de ce Literal
	double valeurAnum = lRatA->getNum();
	double valeurAden = lRatA->getDen();
	const double newVal = valeurB / (valeurAnum / valeurAden); //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivRationalReal */
/* Fin Div */

/* Début Mod */
shared_ptr<Mod> Mod::instance = nullptr;

Mod& Mod::get(){
	if(instance == nullptr){
		instance = shared_ptr<Mod>(new Mod);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Mod::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractMod::addMyself(){
	Mod::get().addBehaviour(typeA, typeB, shared_from_this());
}

/* Début ModIntInt */

const std::shared_ptr<Literal> ModIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB % valeurA; //On effectue l'opération Mod
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin ModIntInt */
/* Fin Mod */

/* Début DivE */
shared_ptr<DivE> DivE::instance = nullptr;

DivE& DivE::get(){
	if(instance == nullptr){
		instance = shared_ptr<DivE>(new DivE);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void DivE::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstarctDivE::addMyself(){
	DivE::get().addBehaviour(typeA, typeB, shared_from_this());
}


/* Début DivEIntInt */

const std::shared_ptr<Literal> DivEIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB / valeurA; //On effectue l'opération DivE
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DivEIntInt */
/* Fin DivE */

/* Début Equ */
shared_ptr<Equ> Equ::instance = nullptr;

Equ& Equ::get(){
	if(instance == nullptr){
		instance = shared_ptr<Equ>(new Equ);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Equ::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractEqu::addMyself(){
	Equ::get().addBehaviour(typeA, typeB, shared_from_this());
}


/* Début EquIntInt */

const std::shared_ptr<Literal> EquIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin EquIntInt */
/* Début EquIntReal */

const std::shared_ptr<Literal> EquIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
  const int newVal = valeurB == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin EquIntReal */
/* Début EquRealInt */

const std::shared_ptr<Literal> EquRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* ldoubleA = dynamic_cast<LReal*>(litA); //On cast ce pointeur en LInteger
	LInteger* lintB = dynamic_cast<LInteger*>(litB);
	double valeurA = ldoubleA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lintB->getValue();
  const int newVal = valeurB == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}

/* Fin EquRealInt */
/* Début EquIntRational */

const std::shared_ptr<Literal> EquIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
  const int newVal = (valeurBnum / valeurBden) == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin EquIntRational */
/* Début EquRationalInt */

const std::shared_ptr<Literal> EquRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurB = lIntB->getValue(); //On récupère la valeur de ce Literal
	int valeurAnum = lRatA->getNum();
	int valeurAden = lRatA->getDen();
  const int newVal = valeurB == (valeurAnum / valeurAden ); //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin EquRationalInt */
/* Début EquRationalRational */

const std::shared_ptr<Literal> EquRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
  const int newVal = (valeurBnum / valeurBden) == (valeurAnum / valeurAden ); //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin EquRationalRational */
/* Début EquRealReal */

const std::shared_ptr<Literal> EquRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
  const int newVal = valeurB == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin EquRealReal */
/* Début EquRealRational */

const std::shared_ptr<Literal> EquRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
  const int newVal = valeurA == (valeurBnum / valeurBden ); //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin EquRealRational */
/* Début EquRationalReal */

const std::shared_ptr<Literal> EquRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce podoubleeur en LReal
	LReal* lRealB = dynamic_cast<LReal*>(litB);
	double valeurB = lRealB->getValue(); //On récupère la valeur de ce Literal
	double valeurAnum = lRatA->getNum();
	double valeurAden = lRatA->getDen();
  const int newVal = valeurB == (valeurAnum / valeurAden ); //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin EquRationalReal */
/* Fin Equ */

/* Début Dif */
shared_ptr<Dif> Dif::instance = nullptr;

Dif& Dif::get(){
	if(instance == nullptr){
		instance = shared_ptr<Dif>(new Dif);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Dif::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractDif::addMyself(){
	Dif::get().addBehaviour(typeA, typeB, shared_from_this());
}


/* Début DifIntInt */

const std::shared_ptr<Literal> DifIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DifIntInt */
/* Début DifIntReal */

const std::shared_ptr<Literal> DifIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
  const int newVal = valeurB != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DifIntReal */
/* Début DifRealInt */

const std::shared_ptr<Literal> DifRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* ldoubleA = dynamic_cast<LReal*>(litA); //On cast ce pointeur en LInteger
	LInteger* lintB = dynamic_cast<LInteger*>(litB);
	double valeurA = ldoubleA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lintB->getValue();
  const int newVal = valeurB != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}

/* Fin DifRealInt */
/* Début DifIntRational */

const std::shared_ptr<Literal> DifIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
  const int newVal = (valeurBnum / valeurBden) != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DifIntRational */
/* Début DifRationalInt */

const std::shared_ptr<Literal> DifRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurB = lIntB->getValue(); //On récupère la valeur de ce Literal
	int valeurAnum = lRatA->getNum();
	int valeurAden = lRatA->getDen();
  const int newVal = valeurB != (valeurAnum / valeurAden ); //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DifRationalInt */
/* Début DifRationalRational */

const std::shared_ptr<Literal> DifRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
  const int newVal = (valeurBnum / valeurBden) != (valeurAnum / valeurAden ); //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DifRationalRational */
/* Début DifRealReal */

const std::shared_ptr<Literal> DifRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
  const int newVal = valeurB != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DifRealReal */
/* Début DifRealRational */

const std::shared_ptr<Literal> DifRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
  const int newVal = valeurA != (valeurBnum / valeurBden ); //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DifRealRational */
/* Début DifRationalReal */

const std::shared_ptr<Literal> DifRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce podoubleeur en LReal
	LReal* lRealB = dynamic_cast<LReal*>(litB);
	double valeurB = lRealB->getValue(); //On récupère la valeur de ce Literal
	double valeurAnum = lRatA->getNum();
	double valeurAden = lRatA->getDen();
  const int newVal = valeurB != (valeurAnum / valeurAden ); //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin DifRationalReal */
/* Fin Dif */

/* Début InfEqu */
shared_ptr<InfEqu> InfEqu::instance = nullptr;

InfEqu& InfEqu::get(){
	if(instance == nullptr){
		instance = shared_ptr<InfEqu>(new InfEqu);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void InfEqu::free(){
	if(instance <= nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractInfEqu::addMyself(){
	InfEqu::get().addBehaviour(typeA, typeB, shared_from_this());
}


/* Début InfEquIntInt */

const std::shared_ptr<Literal> InfEquIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfEquIntInt */
/* Début InfEquIntReal */

const std::shared_ptr<Literal> InfEquIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
  const int newVal = valeurB <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfEquIntReal */
/* Début InfEquRealInt */

const std::shared_ptr<Literal> InfEquRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* ldoubleA = dynamic_cast<LReal*>(litA); //On cast ce pointeur en LInteger
	LInteger* lintB = dynamic_cast<LInteger*>(litB);
	double valeurA = ldoubleA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lintB->getValue();
  const int newVal = valeurB <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}

/* Fin InfEquRealInt */
/* Début InfEquIntRational */

const std::shared_ptr<Literal> InfEquIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
  const int newVal = (valeurBnum / valeurBden) <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfEquIntRational */
/* Début InfEquRationalInt */

const std::shared_ptr<Literal> InfEquRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurB = lIntB->getValue(); //On récupère la valeur de ce Literal
	int valeurAnum = lRatA->getNum();
	int valeurAden = lRatA->getDen();
  const int newVal = valeurB <= (valeurAnum / valeurAden ); //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfEquRationalInt */
/* Début InfEquRationalRational */

const std::shared_ptr<Literal> InfEquRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
  const int newVal = (valeurBnum / valeurBden) <= (valeurAnum / valeurAden ); //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfEquRationalRational */
/* Début InfEquRealReal */

const std::shared_ptr<Literal> InfEquRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
  const int newVal = valeurB <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfEquRealReal */
/* Début InfEquRealRational */

const std::shared_ptr<Literal> InfEquRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
  const int newVal = valeurA <= (valeurBnum / valeurBden ); //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfEquRealRational */
/* Début InfEquRationalReal */

const std::shared_ptr<Literal> InfEquRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce podoubleeur en LReal
	LReal* lRealB = dynamic_cast<LReal*>(litB);
	double valeurB = lRealB->getValue(); //On récupère la valeur de ce Literal
	double valeurAnum = lRatA->getNum();
	double valeurAden = lRatA->getDen();
  const int newVal = valeurB <= (valeurAnum / valeurAden ); //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfEquRationalReal */
/* Fin InfEqu */

/* Début Inf */
shared_ptr<Inf> Inf::instance = nullptr;

Inf& Inf::get(){
	if(instance == nullptr){
		instance = shared_ptr<Inf>(new Inf);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Inf::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractInf::addMyself(){
	Inf::get().addBehaviour(typeA, typeB, shared_from_this());
}


/* Début InfIntInt */

const std::shared_ptr<Literal> InfIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfIntInt */
/* Début InfIntReal */

const std::shared_ptr<Literal> InfIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
  const int newVal = valeurB < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfIntReal */
/* Début InfRealInt */

const std::shared_ptr<Literal> InfRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* ldoubleA = dynamic_cast<LReal*>(litA); //On cast ce pointeur en LInteger
	LInteger* lintB = dynamic_cast<LInteger*>(litB);
	double valeurA = ldoubleA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lintB->getValue();
  const int newVal = valeurB < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}

/* Fin InfRealInt */
/* Début InfIntRational */

const std::shared_ptr<Literal> InfIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
  const int newVal = (valeurBnum / valeurBden) < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfIntRational */
/* Début InfRationalInt */

const std::shared_ptr<Literal> InfRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurB = lIntB->getValue(); //On récupère la valeur de ce Literal
	int valeurAnum = lRatA->getNum();
	int valeurAden = lRatA->getDen();
  const int newVal = valeurB < (valeurAnum / valeurAden ); //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfRationalInt */
/* Début InfRationalRational */

const std::shared_ptr<Literal> InfRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
  const int newVal = (valeurBnum / valeurBden) < (valeurAnum / valeurAden ); //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfRationalRational */
/* Début InfRealReal */

const std::shared_ptr<Literal> InfRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
  const int newVal = valeurB < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfRealReal */
/* Début InfRealRational */

const std::shared_ptr<Literal> InfRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
  const int newVal = valeurA < (valeurBnum / valeurBden ); //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfRealRational */
/* Début InfRationalReal */

const std::shared_ptr<Literal> InfRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce podoubleeur en LReal
	LReal* lRealB = dynamic_cast<LReal*>(litB);
	double valeurB = lRealB->getValue(); //On récupère la valeur de ce Literal
	double valeurAnum = lRatA->getNum();
	double valeurAden = lRatA->getDen();
  const int newVal = valeurB < (valeurAnum / valeurAden ); //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin InfRationalReal */
/* Fin Inf */


/* Début SupEqu */
shared_ptr<SupEqu> SupEqu::instance = nullptr;

SupEqu& SupEqu::get(){
	if(instance == nullptr){
		instance = shared_ptr<SupEqu>(new SupEqu);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void SupEqu::free(){
	if(instance >= nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractSupEqu::addMyself(){
	SupEqu::get().addBehaviour(typeA, typeB, shared_from_this());
}


/* Début SupEquIntInt */

const std::shared_ptr<Literal> SupEquIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupEquIntInt */
/* Début SupEquIntReal */

const std::shared_ptr<Literal> SupEquIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
  const int newVal = valeurB >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupEquIntReal */
/* Début SupEquRealInt */

const std::shared_ptr<Literal> SupEquRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* ldoubleA = dynamic_cast<LReal*>(litA); //On cast ce pointeur en LInteger
	LInteger* lintB = dynamic_cast<LInteger*>(litB);
	double valeurA = ldoubleA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lintB->getValue();
  const int newVal = valeurB >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}

/* Fin SupEquRealInt */
/* Début SupEquIntRational */

const std::shared_ptr<Literal> SupEquIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
  const int newVal = (valeurBnum / valeurBden) >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupEquIntRational */
/* Début SupEquRationalInt */

const std::shared_ptr<Literal> SupEquRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurB = lIntB->getValue(); //On récupère la valeur de ce Literal
	int valeurAnum = lRatA->getNum();
	int valeurAden = lRatA->getDen();
  const int newVal = valeurB >= (valeurAnum / valeurAden ); //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupEquRationalInt */
/* Début SupEquRationalRational */

const std::shared_ptr<Literal> SupEquRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
  const int newVal = (valeurBnum / valeurBden) >= (valeurAnum / valeurAden ); //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupEquRationalRational */
/* Début SupEquRealReal */

const std::shared_ptr<Literal> SupEquRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
  const int newVal = valeurB >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupEquRealReal */
/* Début SupEquRealRational */

const std::shared_ptr<Literal> SupEquRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
  const int newVal = valeurA >= (valeurBnum / valeurBden ); //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupEquRealRational */
/* Début SupEquRationalReal */

const std::shared_ptr<Literal> SupEquRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce podoubleeur en LReal
	LReal* lRealB = dynamic_cast<LReal*>(litB);
	double valeurB = lRealB->getValue(); //On récupère la valeur de ce Literal
	double valeurAnum = lRatA->getNum();
	double valeurAden = lRatA->getDen();
  const int newVal = valeurB >= (valeurAnum / valeurAden ); //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupEquRationalReal */
/* Fin SupEqu */

/* Début Sup */
shared_ptr<Sup> Sup::instance = nullptr;

Sup& Sup::get(){
	if(instance == nullptr){
		instance = shared_ptr<Sup>(new Sup);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Sup::free(){
	if(instance > nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

void AbstractSup::addMyself(){
	Sup::get().addBehaviour(typeA, typeB, shared_from_this());
}


/* Début SupIntInt */

const std::shared_ptr<Literal> SupIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupIntInt */
/* Début SupIntReal */

const std::shared_ptr<Literal> SupIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
  const int newVal = valeurB > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupIntReal */
/* Début SupRealInt */

const std::shared_ptr<Literal> SupRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* ldoubleA = dynamic_cast<LReal*>(litA); //On cast ce pointeur en LInteger
	LInteger* lintB = dynamic_cast<LInteger*>(litB);
	double valeurA = ldoubleA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lintB->getValue();
  const int newVal = valeurB > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}

/* Fin SupRealInt */
/* Début SupIntRational */

const std::shared_ptr<Literal> SupIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
  const int newVal = (valeurBnum / valeurBden) > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupIntRational */
/* Début SupRationalInt */

const std::shared_ptr<Literal> SupRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurB = lIntB->getValue(); //On récupère la valeur de ce Literal
	int valeurAnum = lRatA->getNum();
	int valeurAden = lRatA->getDen();
  const int newVal = valeurB > (valeurAnum / valeurAden ); //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupRationalInt */
/* Début SupRationalRational */

const std::shared_ptr<Literal> SupRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lIntA = dynamic_cast<LRational*>(litA); //On cast ce pointeur en lrational
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	int valeurAnum = lIntA->getNum();
	int valeurAden = lIntA->getDen();
	int valeurBnum = lIntB->getNum();
	int valeurBden = lIntB->getDen();
  const int newVal = (valeurBnum / valeurBden) > (valeurAnum / valeurAden ); //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupRationalRational */
/* Début SupRealReal */

const std::shared_ptr<Literal> SupRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
  const int newVal = valeurB > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupRealReal */
/* Début SupRealRational */

const std::shared_ptr<Literal> SupRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
  const int newVal = valeurA > (valeurBnum / valeurBden ); //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupRealRational */
/* Début SupRationalReal */

const std::shared_ptr<Literal> SupRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LRational* lRatA = dynamic_cast<LRational*>(litA); //On cast ce podoubleeur en LReal
	LReal* lRealB = dynamic_cast<LReal*>(litB);
	double valeurB = lRealB->getValue(); //On récupère la valeur de ce Literal
	double valeurAnum = lRatA->getNum();
	double valeurAden = lRatA->getDen();
  const int newVal = valeurB > (valeurAnum / valeurAden ); //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	return newLit; //On pous notre Literal sur la Stack.
}
/* Fin SupRationalReal */
/* Fin Sup */

/* Début opérateur And */
shared_ptr<And> And::instance = nullptr;

bool And::apply(Stack& s){
	const shared_ptr<Literal> A = s.top();
	s.pop();
	const shared_ptr<Literal> B = s.top();
	s.pop();
	Literal* litA = A.get();
	Literal* litB = B.get();
	if(litA->getType() == linteger && litB->getType() == linteger){
		LInteger* lIntA = dynamic_cast<LInteger*>(litA);
		LInteger* lIntB = dynamic_cast<LInteger*>(litB);
		int valeurA = lIntA->getValue();
		int valeurB = lIntB->getValue();
		if(valeurA == 1 && valeurB == 1){
			const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
			s.push(newLit);
		}
		else{
			const shared_ptr<LInteger> newLit = LInteger::makeLiteral(0);
			s.push(newLit);
		}
	}else{
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
		s.push(newLit);
	}
	return true;
}

And& And::get(){
	if(instance == nullptr){
		instance = shared_ptr<And>(new And);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void And::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
/* fin opérateur And */

/* Début opérateur Or */
shared_ptr<Or> Or::instance = nullptr;

bool Or::apply(Stack& s){
	const shared_ptr<Literal> A = s.top();
	s.pop();
	const shared_ptr<Literal> B = s.top();
	s.pop();
	Literal* litA = A.get();
	Literal* litB = B.get();
	if(litA->getType() == linteger && litB->getType() == linteger){
		LInteger* lIntA = dynamic_cast<LInteger*>(litA);
		LInteger* lIntB = dynamic_cast<LInteger*>(litB);
		int valeurA = lIntA->getValue();
		int valeurB = lIntB->getValue();
		if(valeurA == 0 && valeurB == 0){
			const shared_ptr<LInteger> newLit = LInteger::makeLiteral(0);
			s.push(newLit);
		}
		else{
			const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
			s.push(newLit);
		}
	}else{
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(1);
		s.push(newLit);
	}
	return true;
}

Or& Or::get(){
	if(instance == nullptr){
		instance = shared_ptr<Or>(new Or);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Or::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
/* fin opérateur Or */

/* Début opérateur Swap */
shared_ptr<Swap> Swap::instance = nullptr;

bool Swap::apply(Stack& s){
	const shared_ptr<Literal> A = s.top();
	s.pop();
	const shared_ptr<Literal> B = s.top();
	s.pop();
	s.push(A);
	s.push(B);
	return true;
}

Swap& Swap::get(){
	if(instance == nullptr){
		instance = shared_ptr<Swap>(new Swap);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Swap::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
/* fin opérateur Swap */

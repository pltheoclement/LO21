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
	this->possibles[std::make_pair(A,B)]=a;
}

bool BinaryOperator::apply(Stack& s){

	if(s.size() < 2)
		throw OperatorException("Need 2 elements in the stack");
	else{
		const std::shared_ptr<Literal> elA = s.top();// le premier argument
		s.pop();

		const std::shared_ptr<Literal> elB = s.top();// le deuxième
		s.pop();

		LiteralType A=elA->getType();

		LiteralType B=elB->getType();

		if (possibles.count(make_pair(A, B)) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
			auto opp = possibles.at(make_pair(A,B));
            try{
                const shared_ptr<Literal> res = opp->execution(elA, elB);
                s.push(res);
            }catch(OperatorException& e){
                s.push(elB);
                s.push(elA);
                throw e;
            }
            return true;
		}else{
			s.push(elB);
			s.push(elA);
			throw OperatorException("The operator you entered does not exist for the type of the top 2 elements of the stack");
			return false;
		}
	}
}

void AbstractAdd::addMyself(){
	Add::get().addBehaviour(this->typeA, this->typeB, shared_from_this());
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin AddIntInt */
/* Début AddIntReal */

const std::shared_ptr<Literal> AddIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const double newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	return newLit;
}
/* Fin AddIntReal */
/* Début AddRealInt */

const std::shared_ptr<Literal> AddRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return (AddIntReal::execution(B, A));
}
/* Fin AddRealInt */
/* Début AddIntRational */

const std::shared_ptr<Literal> AddIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newNum = valeurA * valeurBden + valeurBnum; //On effectue l'opération Add
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurBden);
	return newLit;
}
/* Fin AddIntRational */
/* Début AddRationalInt */

const std::shared_ptr<Literal> AddRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return AddIntRational::execution(B, A);
}
/* Fin AddRationalInt */
/* Début AddRationalRational */
const std::shared_ptr<Literal> AddRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newNum = valeurAnum * valeurBden + valeurBnum * valeurAden; //On effectue l'opération Add
	const int newDen = valeurBden * valeurAden;
	const shared_ptr<LRational> lit = LRational::makeLiteral(newNum, newDen);
	if(lit->getDen() == 1){
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(lit->getNum());
		return newLit;
	}else{
		return lit;
	}
}
/* Fin AddRationalRational */
/* Début AddRealReal */

const std::shared_ptr<Literal> AddRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const double newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
}
/* Fin AddRealReal */
/* Début AddRealRational */

const std::shared_ptr<Literal> AddRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const double newVal = valeurA + (valeurBnum / valeurBden); //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurA * valeurB; //On effectue l'opération Mul
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin MulIntInt */
/* Début MulIntReal */

const std::shared_ptr<Literal> MulIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const double newVal = valeurA * valeurB; //On effectue l'opération Mul
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	return newLit;
}
/* Fin MulIntReal */
/* Début MulRealInt */

const std::shared_ptr<Literal> MulRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return MulIntReal::execution(B, A);
}
/* Fin MulRealInt */
/* Début MulIntRational */

const std::shared_ptr<Literal> MulIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newNum = valeurA * valeurBnum; //On effectue l'opération Mul
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurBden);
	return newLit;
}
/* Fin MulIntRational */
/* Début MulRationalInt */

const std::shared_ptr<Literal> MulRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return MulIntRational::execution(B, A);
}
/* Fin MulRationalInt */
/* Début MulRationalRational */

const std::shared_ptr<Literal> MulRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newNum = valeurAnum * valeurBnum; //On effectue l'opération Mul
	const int newDen = valeurBden * valeurAden;
	const shared_ptr<LRational> lit = LRational::makeLiteral(newNum, newDen);
	if(lit->getDen() == 1){
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(lit->getNum());
		return newLit;
	}else{
		return lit;
	}
}
/* Fin MulRationalRational */
/* Début MulRealReal */

const std::shared_ptr<Literal> MulRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const double newVal = valeurA * valeurB; //On effectue l'opération Mul
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
}
/* Fin MulRealReal */
/* Début MulRealRational */

const std::shared_ptr<Literal> MulRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const double newVal = valeurA * (valeurBnum / valeurBden); //On effectue l'opération Mul
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurB - valeurA; //On effectue l'opération Sub
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SubIntInt */
/* Début SubIntReal */

const std::shared_ptr<Literal> SubIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const double newVal = valeurB - valeurA; //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	return newLit;
}
/* Fin SubIntReal */
/* Début SubRealInt */

const std::shared_ptr<Literal> SubRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	double valeurA = getValueReal(A);
	const double newVal = valeurB - valeurA; //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	return newLit;
}

/* Fin SubRealInt */
/* Début SubIntRational */

const std::shared_ptr<Literal> SubIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newNum = valeurBnum - (valeurA * valeurBden); //On effectue l'opération Sub
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurBden);
	return newLit;
}
/* Fin SubIntRational */
/* Début SubRationalInt */

const std::shared_ptr<Literal> SubRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newNum = (valeurB * valeurAden) - valeurAnum; //On effectue l'opération Sub
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurAden);
	return newLit;
}
/* Fin SubRationalInt */
/* Début SubRationalRational */

const std::shared_ptr<Literal> SubRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newNum = valeurAden * valeurBnum - valeurAnum * valeurBden; //On effectue l'opération Sub
	const int newDen = valeurBden * valeurAden;
	const shared_ptr<LRational> lit = LRational::makeLiteral(newNum, newDen);
	if(lit->getDen() == 1){
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(lit->getNum());
		return newLit;
	}else{
		return lit;
	}
}
/* Fin SubRationalRational */
/* Début SubRealReal */

const std::shared_ptr<Literal> SubRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const double newVal = valeurB - valeurA; //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
}
/* Fin SubRealReal */
/* Début SubRealRational */

const std::shared_ptr<Literal> SubRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const double newVal = (valeurBnum / valeurBden) - valeurA; //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
}
/* Fin SubRealRational */
/* Début SubRationalReal */

const std::shared_ptr<Literal> SubRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurB = getValueReal(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const double newVal = valeurB - (valeurAnum / valeurAden); //On effectue l'opération Sub
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
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
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	if(valeurA == 0){
		throw OperatorException("Divided by 0");
	}
	double valeurB = getValueInteger(B);
	const double newVal = valeurB / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	return newLit;
}
/* Fin DivIntInt */
/* Début DivIntReal */

const std::shared_ptr<Literal> DivIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	if(valeurA == 0){
		throw OperatorException("Divided by 0");
	}
	double valeurB = getValueReal(B);
	const double newVal = valeurB / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	return newLit;
}
/* Fin DivIntReal */
/* Début DivRealInt */

const std::shared_ptr<Literal> DivRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	if(valeurA == 0){
		throw OperatorException("Divided by 0");
	}
	double valeurB = getValueInteger(B);
	const double newVal = valeurB / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal);
	return newLit;
}

/* Fin DivRealInt */
/* Début DivIntRational */

const std::shared_ptr<Literal> DivIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	if(valeurBnum == 0){
		throw OperatorException("Divided by 0");
	}
	const int newNum = (valeurBden * valeurA); //On effectue l'opération Div
	const shared_ptr<LRational> lit = LRational::makeLiteral(newNum, valeurBden);
	if(lit->getDen() == 1){
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(lit->getNum());
		return newLit;
	}else{
		return lit;
	}
}
/* Fin DivIntRational */
/* Début DivRationalInt */

const std::shared_ptr<Literal> DivRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	if(valeurAnum == 0){
		throw OperatorException("Divided by 0");
	}
	const int newNum = (valeurB * valeurAden); //On effectue l'opération Div
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurAnum);
	return newLit;
}
/* Fin DivRationalInt */
/* Début DivRationalRational */

const std::shared_ptr<Literal> DivRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newNum = valeurAnum * valeurBden; //On effectue l'opération Div
	const int newDen = valeurBnum * valeurAden;
	if(newDen == 0){
		throw OperatorException("Divided by 0");
	}
	const shared_ptr<LRational> lit = LRational::makeLiteral(newNum, newDen);
	if(lit->getDen() == 1){
		const shared_ptr<LInteger> newLit = LInteger::makeLiteral(lit->getNum());
		return newLit;
	}else{
		return lit;
	}
}
/* Fin DivRationalRational */
/* Début DivRealReal */

const std::shared_ptr<Literal> DivRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	if(valeurA == 0){
		throw OperatorException("Divided by 0");
	}
	double valeurB = getValueReal(B);
	const double newVal = valeurB / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
}
/* Fin DivRealReal */
/* Début DivRealRational */

const std::shared_ptr<Literal> DivRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	if(valeurA == 0){
		throw OperatorException("Divided by 0");
	}
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const double newVal = (valeurBnum / valeurBden) / valeurA; //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
}
/* Fin DivRealRational */
/* Début DivRationalReal */

const std::shared_ptr<Literal> DivRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurB = getValueReal(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	if(valeurAnum == 0){
		throw OperatorException("Divided by 0");
	}
	if(valeurAden == 0){
		throw OperatorException("Divided by 0");
	}
	const double newVal = valeurB / (valeurAnum / valeurAden); //On effectue l'opération Div
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	if(valeurA == 0){
		throw OperatorException("Divided by 0");
	}
	int valeurB = getValueInteger(B);
	const int newVal = valeurB % valeurA; //On effectue l'opération Mod
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	if(valeurA == 0){
		throw OperatorException("Divided by 0");
	}
	int valeurB = getValueInteger(B);
	const int newVal = valeurB / valeurA; //On effectue l'opération DivE
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurB == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin EquIntInt */
/* Début EquIntReal */

const std::shared_ptr<Literal> EquIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin EquIntReal */
/* Début EquRealInt */

const std::shared_ptr<Literal> EquRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	double valeurA = getValueReal(A);
	const int newVal = valeurB == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}

/* Fin EquRealInt */
/* Début EquIntRational */

const std::shared_ptr<Literal> EquIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin EquIntRational */
/* Début EquRationalInt */

const std::shared_ptr<Literal> EquRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB == (valeurAnum / valeurAden ); //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin EquRationalInt */
/* Début EquRationalRational */

const std::shared_ptr<Literal> EquRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) == (valeurAnum / valeurAden ); //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin EquRationalRational */
/* Début EquRealReal */

const std::shared_ptr<Literal> EquRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB == valeurA; //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin EquRealReal */
/* Début EquRealRational */

const std::shared_ptr<Literal> EquRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = valeurA == (valeurBnum / valeurBden ); //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin EquRealRational */
/* Début EquRationalReal */

const std::shared_ptr<Literal> EquRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurB = getValueReal(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB == (valeurAnum / valeurAden ); //On effectue l'opération Equ
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurB != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin DifIntInt */
/* Début DifIntReal */

const std::shared_ptr<Literal> DifIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin DifIntReal */
/* Début DifRealInt */

const std::shared_ptr<Literal> DifRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	double valeurA = getValueReal(A);
	const int newVal = valeurB != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}

/* Fin DifRealInt */
/* Début DifIntRational */

const std::shared_ptr<Literal> DifIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin DifIntRational */
/* Début DifRationalInt */

const std::shared_ptr<Literal> DifRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB != (valeurAnum / valeurAden ); //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin DifRationalInt */
/* Début DifRationalRational */

const std::shared_ptr<Literal> DifRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) != (valeurAnum / valeurAden ); //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin DifRationalRational */
/* Début DifRealReal */

const std::shared_ptr<Literal> DifRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB != valeurA; //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin DifRealReal */
/* Début DifRealRational */

const std::shared_ptr<Literal> DifRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = valeurA != (valeurBnum / valeurBden ); //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin DifRealRational */
/* Début DifRationalReal */

const std::shared_ptr<Literal> DifRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurB = getValueReal(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB != (valeurAnum / valeurAden ); //On effectue l'opération Dif
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurB <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfEquIntInt */
/* Début InfEquIntReal */

const std::shared_ptr<Literal> InfEquIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfEquIntReal */
/* Début InfEquRealInt */

const std::shared_ptr<Literal> InfEquRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	double valeurA = getValueReal(A);
	const int newVal = valeurB <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}

/* Fin InfEquRealInt */
/* Début InfEquIntRational */

const std::shared_ptr<Literal> InfEquIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfEquIntRational */
/* Début InfEquRationalInt */

const std::shared_ptr<Literal> InfEquRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB <= (valeurAnum / valeurAden ); //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfEquRationalInt */
/* Début InfEquRationalRational */

const std::shared_ptr<Literal> InfEquRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) <= (valeurAnum / valeurAden ); //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfEquRationalRational */
/* Début InfEquRealReal */

const std::shared_ptr<Literal> InfEquRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB <= valeurA; //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfEquRealReal */
/* Début InfEquRealRational */

const std::shared_ptr<Literal> InfEquRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = valeurA <= (valeurBnum / valeurBden ); //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfEquRealRational */
/* Début InfEquRationalReal */

const std::shared_ptr<Literal> InfEquRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurB = getValueReal(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB <= (valeurAnum / valeurAden ); //On effectue l'opération InfEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurB < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfIntInt */
/* Début InfIntReal */

const std::shared_ptr<Literal> InfIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfIntReal */
/* Début InfRealInt */

const std::shared_ptr<Literal> InfRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurB < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}

/* Fin InfRealInt */
/* Début InfIntRational */

const std::shared_ptr<Literal> InfIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfIntRational */
/* Début InfRationalInt */

const std::shared_ptr<Literal> InfRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB < (valeurAnum / valeurAden ); //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfRationalInt */
/* Début InfRationalRational */

const std::shared_ptr<Literal> InfRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) < (valeurAnum / valeurAden ); //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfRationalRational */
/* Début InfRealReal */

const std::shared_ptr<Literal> InfRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB < valeurA; //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfRealReal */
/* Début InfRealRational */

const std::shared_ptr<Literal> InfRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = valeurA < (valeurBnum / valeurBden ); //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin InfRealRational */
/* Début InfRationalReal */

const std::shared_ptr<Literal> InfRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurB = getValueReal(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB < (valeurAnum / valeurAden ); //On effectue l'opération Inf
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurB >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupEquIntInt */
/* Début SupEquIntReal */

const std::shared_ptr<Literal> SupEquIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupEquIntReal */
/* Début SupEquRealInt */

const std::shared_ptr<Literal> SupEquRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	double valeurA = getValueReal(A);
	const int newVal = valeurB >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}

/* Fin SupEquRealInt */
/* Début SupEquIntRational */

const std::shared_ptr<Literal> SupEquIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupEquIntRational */
/* Début SupEquRationalInt */

const std::shared_ptr<Literal> SupEquRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB >= (valeurAnum / valeurAden ); //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupEquRationalInt */
/* Début SupEquRationalRational */

const std::shared_ptr<Literal> SupEquRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) >= (valeurAnum / valeurAden ); //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupEquRationalRational */
/* Début SupEquRealReal */

const std::shared_ptr<Literal> SupEquRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB >= valeurA; //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupEquRealReal */
/* Début SupEquRealRational */

const std::shared_ptr<Literal> SupEquRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = valeurA >= (valeurBnum / valeurBden ); //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupEquRealRational */
/* Début SupEquRationalReal */

const std::shared_ptr<Literal> SupEquRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurB = getValueReal(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB >= (valeurAnum / valeurAden ); //On effectue l'opération SupEqu
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
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
	int valeurA = getValueInteger(A); //On récupère la valeur de ces deux Literal
	int valeurB = getValueInteger(B);
	const int newVal = valeurB > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupIntInt */
/* Début SupIntReal */

const std::shared_ptr<Literal> SupIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupIntReal */
/* Début SupRealInt */

const std::shared_ptr<Literal> SupRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	double valeurA = getValueReal(A);
	const int newVal = valeurB > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}

/* Fin SupRealInt */
/* Début SupIntRational */

const std::shared_ptr<Literal> SupIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurA = getValueInteger(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupIntRational */
/* Début SupRationalInt */

const std::shared_ptr<Literal> SupRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	int valeurB = getValueInteger(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB > (valeurAnum / valeurAden ); //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupRationalInt */
/* Début SupRationalRational */

const std::shared_ptr<Literal> SupRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = (valeurBnum / valeurBden) > (valeurAnum / valeurAden ); //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupRationalRational */
/* Début SupRealReal */

const std::shared_ptr<Literal> SupRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	double valeurB = getValueReal(B);
	const int newVal = valeurB > valeurA; //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupRealReal */
/* Début SupRealRational */

const std::shared_ptr<Literal> SupRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurA = getValueReal(A); //On récupère la valeur de ce Literal
	pair<int, int> valeurB = getValueRational(B);
	double valeurBnum = valeurB.first;
	double valeurBden = valeurB.second;
	const int newVal = valeurA > (valeurBnum / valeurBden ); //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupRealRational */
/* Début SupRationalReal */

const std::shared_ptr<Literal> SupRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	double valeurB = getValueReal(B); //On récupère la valeur de ce Literal
	pair<int, int> valeurA = getValueRational(A);
	double valeurAnum = valeurA.first;
	double valeurAden = valeurA.second;
	const int newVal = valeurB > (valeurAnum / valeurAden ); //On effectue l'opération Sup
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal);
	return newLit;
}
/* Fin SupRationalReal */
/* Fin Sup */

/* Début opérateur And */
shared_ptr<And> And::instance = nullptr;

bool And::apply(Stack& s){
	if(s.size() < 2)
			throw OperatorException("Need 2 elements in the stack");
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
	if(s.size() < 2)
			throw OperatorException("Need 2 elements in the stack");
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
	if(s.size() < 2)
			throw OperatorException("Need 2 elements in the stack");
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

/* Début opérateur Sto */
shared_ptr<Sto> Sto::instance = nullptr;

bool Sto::apply(Stack& s){
	if(s.size() < 2)
			throw OperatorException("Need 2 elements in the stack");
	const shared_ptr<Literal> A = s.top();
	s.pop();
	const shared_ptr<Literal> B = s.top();
	if(A.get()->getType() != lexpression){
		s.push(B);
		throw OperatorException("Need an expression");
	}else{
		s.pop();
		Literal* litA = A.get();
		LExpression* lexpA = dynamic_cast<LExpression*>(litA);
		string var = lexpA->getValue();
		Computer::getInstance().storeVariable(var, *B);
	}
	return true;
}

Sto& Sto::get(){
	if(instance == nullptr){
		instance = shared_ptr<Sto>(new Sto);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Sto::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
/* fin opérateur Sto */

/* Début opérateur Ift */
shared_ptr<Ift> Ift::instance = nullptr;

bool Ift::apply(Stack& s){
	if(s.size() < 2)
		throw OperatorException("Need 2 elements in the stack");
	const shared_ptr<Literal> A = s.top();
	s.pop();
	const shared_ptr<Literal> B = s.top();
	s.pop();
	if(B.get()->getType() == linteger){

		Literal* litB = B.get();
		LInteger* lintB = dynamic_cast<LInteger*>(litB);
		int boolean = lintB->getValue();
		if(boolean == 0){
			return true;
		}
	}
	if(A.get()->getType() == lprogram || A.get()->getType() == lexpression){
		s.push(A);
		Operator::getOperator("EVAL").apply(Stack::getInstance());
		return true;
	}else{
		s.push(B);
		s.push(A);
		throw OperatorException("Need an expression or a program");
	}
}

Ift& Ift::get(){
	if(instance == nullptr){
		instance = shared_ptr<Ift>(new Ift);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Ift::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}
/* fin opérateur Ift */

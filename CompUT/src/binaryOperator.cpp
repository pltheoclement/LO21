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

bool BinaryOperator::apply(Stack& s){

	const std::shared_ptr<Literal> elA = s.top();// le premier argument

	const std::shared_ptr<Literal> elB = s.top();// le deuxième

    LiteralType A=elA->getType();

    LiteralType B=elB->getType();

    if (possibles.count(make_pair(A, B)) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
    	const shared_ptr<Literal> res = possibles[make_pair(A,B)]->execution(elA, elB);
    	s.pop();
    	s.pop();
    	s.push(res);
    	return true;
    }else{
    	return false;
    }
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
AddIntInt::AddIntInt(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddIntInt si on recherche l'opérateur Add pour deux Int.
}
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
AddIntReal::AddIntReal(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddIntReal si on recherche l'opérateur Add pour deux Int.
}
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
AddRealInt::AddRealInt(){
	Add::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRealInt si on recherche l'opérateur Add pour deux Int.
}
const std::shared_ptr<Literal> AddRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return (AddIntReal::execution(B, A));
}
/* Fin AddRealInt */
/* Début AddIntRational */
AddIntRational::AddIntRational(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddIntRational si on recherche l'opérateur Add pour deux Int.
}
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
AddRationalInt::AddRationalInt(){
	Add::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRationalInt si on recherche l'opérateur Add pour deux Int.
}
const std::shared_ptr<Literal> AddRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return AddIntRational::execution(B, A);
}
/* Fin AddRationalInt */
/* Début AddRationalRational */
AddRationalRational::AddRationalRational(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRationalRational si on recherche l'opérateur Add pour deux Int.
}
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
AddRealReal::AddRealReal(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRealReal si on recherche l'opérateur Add pour deux Int.
}
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
AddRealRational::AddRealRational(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRealRational si on recherche l'opérateur Add pour deux Int.
}
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
AddRationalReal::AddRationalReal(){
	Add::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRealInt si on recherche l'opérateur Add pour deux Int.
}
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

/* Début MulIntInt */
MulIntInt::MulIntInt(){
	Mul::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulIntInt si on recherche l'opérateur Mul pour deux Int.
}
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
MulIntReal::MulIntReal(){
	Mul::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulIntReal si on recherche l'opérateur Mul pour deux Int.
}
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
MulRealInt::MulRealInt(){
	Mul::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulRealInt si on recherche l'opérateur Mul pour deux Int.
}
const std::shared_ptr<Literal> MulRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return MulIntReal::execution(B, A);
}
/* Fin MulRealInt */
/* Début MulIntRational */
MulIntRational::MulIntRational(){
	Mul::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulIntRational si on recherche l'opérateur Mul pour deux Int.
}
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
MulRationalInt::MulRationalInt(){
		Mul::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulRationalInt si on recherche l'opérateur Mul pour deux Int.
}
const std::shared_ptr<Literal> MulRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	return MulIntRational::execution(B, A);
}
/* Fin MulRationalInt */
/* Début MulRationalRational */
MulRationalRational::MulRationalRational(){
	Mul::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulRationalRational si on recherche l'opérateur Mul pour deux Int.
}
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
MulRealReal::MulRealReal(){
	Mul::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulRealReal si on recherche l'opérateur Mul pour deux Int.
}
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
MulRealRational::MulRealRational(){
	Mul::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulRealRational si on recherche l'opérateur Mul pour deux Int.
}
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
MulRationalReal::MulRationalReal(){
	Mul::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Mul, qui permettra de trouver un objet de la classe MulRealInt si on recherche l'opérateur Mul pour deux Int.
}
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

/* Début SubIntInt */
SubIntInt::SubIntInt(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubIntInt si on recherche l'opérateur Sub pour deux Int.
}
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
SubIntReal::SubIntReal(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubIntReal si on recherche l'opérateur Sub pour deux Int.
}
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
SubRealInt::SubRealInt(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubRealInt si on recherche l'opérateur Sub pour deux Int.
}
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
SubIntRational::SubIntRational(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubIntRational si on recherche l'opérateur Sub pour deux Int.
}
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
SubRationalInt::SubRationalInt(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubRationalInt si on recherche l'opérateur Sub pour deux Int.
}
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
SubRationalRational::SubRationalRational(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubRationalRational si on recherche l'opérateur Sub pour deux Int.
}
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
SubRealReal::SubRealReal(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubRealReal si on recherche l'opérateur Sub pour deux Int.
}
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
SubRealRational::SubRealRational(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubRealRational si on recherche l'opérateur Sub pour deux Int.
}
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
SubRationalReal::SubRationalReal(){
	Sub::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sub, qui permettra de trouver un objet de la classe SubRealInt si on recherche l'opérateur Sub pour deux Int.
}
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

/* Début DivIntInt */
DivIntInt::DivIntInt(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivIntInt si on recherche l'opérateur Div pour deux Int.
}
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
DivIntReal::DivIntReal(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivIntReal si on recherche l'opérateur Div pour deux Int.
}
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
DivRealInt::DivRealInt(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivRealInt si on recherche l'opérateur Div pour deux Int.
}
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
DivIntRational::DivIntRational(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivIntRational si on recherche l'opérateur Div pour deux Int.
}
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
DivRationalInt::DivRationalInt(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivRationalInt si on recherche l'opérateur Div pour deux Int.
}
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
DivRationalRational::DivRationalRational(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivRationalRational si on recherche l'opérateur Div pour deux Int.
}
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
DivRealReal::DivRealReal(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivRealReal si on recherche l'opérateur Div pour deux Int.
}
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
DivRealRational::DivRealRational(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivRealRational si on recherche l'opérateur Div pour deux Int.
}
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
DivRationalReal::DivRationalReal(){
	Div::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Div, qui permettra de trouver un objet de la classe DivRealInt si on recherche l'opérateur Div pour deux Int.
}
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

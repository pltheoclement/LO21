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

/* Début ModIntInt */
ModIntInt::ModIntInt(){
	Mod::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Mod, qui permettra de trouver un objet de la classe ModIntInt si on recherche l'opérateur Mod pour deux Int.
}
const std::shared_ptr<Literal> ModIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurB % valeurA; //On effectue l'opération Mod
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
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

/* Début DivEIntInt */
DivEIntInt::DivEIntInt(){
	DivE::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de DivE, qui permettra de trouver un objet de la classe DivEIntInt si on recherche l'opérateur DivE pour deux Int.
}
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

/* Début EquIntInt */
EquIntInt::EquIntInt(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquIntInt si on recherche l'opérateur Equ pour deux Int.
}
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
EquIntReal::EquIntReal(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquIntReal si on recherche l'opérateur Equ pour deux Int.
}
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
EquRealInt::EquRealInt(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquRealInt si on recherche l'opérateur Equ pour deux Int.
}
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
EquIntRational::EquIntRational(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquIntRational si on recherche l'opérateur Equ pour deux Int.
}
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
EquRationalInt::EquRationalInt(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquRationalInt si on recherche l'opérateur Equ pour deux Int.
}
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
EquRationalRational::EquRationalRational(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquRationalRational si on recherche l'opérateur Equ pour deux Int.
}
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
EquRealReal::EquRealReal(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquRealReal si on recherche l'opérateur Equ pour deux Int.
}
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
EquRealRational::EquRealRational(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquRealRational si on recherche l'opérateur Equ pour deux Int.
}
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
EquRationalReal::EquRationalReal(){
	Equ::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Equ, qui permettra de trouver un objet de la classe EquRealInt si on recherche l'opérateur Equ pour deux Int.
}
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

/* Début DifIntInt */
DifIntInt::DifIntInt(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifIntInt si on recherche l'opérateur Dif pour deux Int.
}
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
DifIntReal::DifIntReal(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifIntReal si on recherche l'opérateur Dif pour deux Int.
}
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
DifRealInt::DifRealInt(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifRealInt si on recherche l'opérateur Dif pour deux Int.
}
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
DifIntRational::DifIntRational(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifIntRational si on recherche l'opérateur Dif pour deux Int.
}
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
DifRationalInt::DifRationalInt(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifRationalInt si on recherche l'opérateur Dif pour deux Int.
}
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
DifRationalRational::DifRationalRational(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifRationalRational si on recherche l'opérateur Dif pour deux Int.
}
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
DifRealReal::DifRealReal(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifRealReal si on recherche l'opérateur Dif pour deux Int.
}
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
DifRealRational::DifRealRational(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifRealRational si on recherche l'opérateur Dif pour deux Int.
}
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
DifRationalReal::DifRationalReal(){
	Dif::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Dif, qui permettra de trouver un objet de la classe DifRealInt si on recherche l'opérateur Dif pour deux Int.
}
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

/* Début InfEquIntInt */
InfEquIntInt::InfEquIntInt(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquIntInt si on recherche l'opérateur InfEqu pour deux Int.
}
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
InfEquIntReal::InfEquIntReal(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquIntReal si on recherche l'opérateur InfEqu pour deux Int.
}
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
InfEquRealInt::InfEquRealInt(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquRealInt si on recherche l'opérateur InfEqu pour deux Int.
}
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
InfEquIntRational::InfEquIntRational(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquIntRational si on recherche l'opérateur InfEqu pour deux Int.
}
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
InfEquRationalInt::InfEquRationalInt(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquRationalInt si on recherche l'opérateur InfEqu pour deux Int.
}
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
InfEquRationalRational::InfEquRationalRational(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquRationalRational si on recherche l'opérateur InfEqu pour deux Int.
}
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
InfEquRealReal::InfEquRealReal(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquRealReal si on recherche l'opérateur InfEqu pour deux Int.
}
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
InfEquRealRational::InfEquRealRational(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquRealRational si on recherche l'opérateur InfEqu pour deux Int.
}
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
InfEquRationalReal::InfEquRationalReal(){
	InfEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de InfEqu, qui permettra de trouver un objet de la classe InfEquRealInt si on recherche l'opérateur InfEqu pour deux Int.
}
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

/* Début InfIntInt */
InfIntInt::InfIntInt(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfIntInt si on recherche l'opérateur Inf pour deux Int.
}
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
InfIntReal::InfIntReal(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfIntReal si on recherche l'opérateur Inf pour deux Int.
}
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
InfRealInt::InfRealInt(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfRealInt si on recherche l'opérateur Inf pour deux Int.
}
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
InfIntRational::InfIntRational(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfIntRational si on recherche l'opérateur Inf pour deux Int.
}
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
InfRationalInt::InfRationalInt(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfRationalInt si on recherche l'opérateur Inf pour deux Int.
}
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
InfRationalRational::InfRationalRational(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfRationalRational si on recherche l'opérateur Inf pour deux Int.
}
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
InfRealReal::InfRealReal(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfRealReal si on recherche l'opérateur Inf pour deux Int.
}
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
InfRealRational::InfRealRational(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfRealRational si on recherche l'opérateur Inf pour deux Int.
}
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
InfRationalReal::InfRationalReal(){
	Inf::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Inf, qui permettra de trouver un objet de la classe InfRealInt si on recherche l'opérateur Inf pour deux Int.
}
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

/* Début SupEquIntInt */
SupEquIntInt::SupEquIntInt(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquIntInt si on recherche l'opérateur SupEqu pour deux Int.
}
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
SupEquIntReal::SupEquIntReal(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquIntReal si on recherche l'opérateur SupEqu pour deux Int.
}
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
SupEquRealInt::SupEquRealInt(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquRealInt si on recherche l'opérateur SupEqu pour deux Int.
}
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
SupEquIntRational::SupEquIntRational(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquIntRational si on recherche l'opérateur SupEqu pour deux Int.
}
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
SupEquRationalInt::SupEquRationalInt(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquRationalInt si on recherche l'opérateur SupEqu pour deux Int.
}
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
SupEquRationalRational::SupEquRationalRational(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquRationalRational si on recherche l'opérateur SupEqu pour deux Int.
}
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
SupEquRealReal::SupEquRealReal(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquRealReal si on recherche l'opérateur SupEqu pour deux Int.
}
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
SupEquRealRational::SupEquRealRational(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquRealRational si on recherche l'opérateur SupEqu pour deux Int.
}
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
SupEquRationalReal::SupEquRationalReal(){
	SupEqu::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de SupEqu, qui permettra de trouver un objet de la classe SupEquRealInt si on recherche l'opérateur SupEqu pour deux Int.
}
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

/* Début SupIntInt */
SupIntInt::SupIntInt(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupIntInt si on recherche l'opérateur Sup pour deux Int.
}
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
SupIntReal::SupIntReal(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupIntReal si on recherche l'opérateur Sup pour deux Int.
}
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
SupRealInt::SupRealInt(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupRealInt si on recherche l'opérateur Sup pour deux Int.
}
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
SupIntRational::SupIntRational(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupIntRational si on recherche l'opérateur Sup pour deux Int.
}
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
SupRationalInt::SupRationalInt(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupRationalInt si on recherche l'opérateur Sup pour deux Int.
}
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
SupRationalRational::SupRationalRational(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupRationalRational si on recherche l'opérateur Sup pour deux Int.
}
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
SupRealReal::SupRealReal(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupRealReal si on recherche l'opérateur Sup pour deux Int.
}
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
SupRealRational::SupRealRational(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupRealRational si on recherche l'opérateur Sup pour deux Int.
}
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
SupRationalReal::SupRationalReal(){
	Sup::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Sup, qui permettra de trouver un objet de la classe SupRealInt si on recherche l'opérateur Sup pour deux Int.
}
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
  const shared_ptr<Literal> B = s.top();
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
  const shared_ptr<Literal> B = s.top();
	Literal* litA = A.get();
  Literal* litB = B.get();
	if(litA->getType() == linteger && litB->getType() == linteger){
		LInteger* lIntA = dynamic_cast<LInteger*>(litA);
    LInteger* lIntB = dynamic_cast<LInteger*>(litB);
		int valeurA = lIntA->getValue();
    int valeurB = lIntB->getValue();
    if(valeurA == 1 || valeurB == 1){
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
  s.push(B);
  s.push(A);
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

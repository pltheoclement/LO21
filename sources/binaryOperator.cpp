/*
 * concreteBinaryOperator.cpp
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */

#include <iostream>
#include <string>
#include <map>

#include "../headers/operator.h"
#include "../headers/binaryOperator.h"
#include "../headers/stack.h"
#include "../headers/literal.h"

using namespace std;

void BinaryOperator::apply(Stack& s){

	const std::shared_ptr<Literal> elA = s.top();// le premier argument

	const std::shared_ptr<Literal> elB = s.top();// le deuxième

    LiteralType A=elA->getType();

    LiteralType B=elB->getType();

    if (possibles.count(make_pair(A, B)) > 0) {// existe bien dans ta map then possibles[make_pair(A,B)].execution(); // @suppress("Method cannot be resolved")
    	possibles[make_pair(A,B)]->execution(elA, elB);
    	s.pop();
    	s.pop();
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
void AddIntInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LInteger* lIntB = dynamic_cast<LInteger*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurB = lIntB->getValue();
	const int newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LInteger> newLit = LInteger::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	Stack::getInstance().push(newLit); //On pous notre Literal sur la Stack.
}
/* Fin AddIntInt */
/* Début AddIntReal */
AddIntReal::AddIntReal(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddIntReal si on recherche l'opérateur Add pour deux Int.
}
void AddIntReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LReal* lDoubleB = dynamic_cast<LReal*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lDoubleB->getValue();
	const double newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau int
	Stack::getInstance().push(newLit); //On pous notre Literal sur la Stack.
}
/* Fin AddIntReal */
/* Début AddRealInt */
AddRealInt::AddRealInt(){
	Add::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRealInt si on recherche l'opérateur Add pour deux Int.
}
void AddRealInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	AddIntReal::execution(B, A);
}
/* Fin AddRealInt */
/* Début AddIntRational */
AddIntRational::AddIntRational(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddIntRational si on recherche l'opérateur Add pour deux Int.
}
void AddIntRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LInteger* lIntA = dynamic_cast<LInteger*>(litA); //On cast ce pointeur en LInteger
	LRational* lRatB = dynamic_cast<LRational*>(litB);
	int valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	int valeurBnum = lRatB->getNum();
	int valeurBden = lRatB->getDen();
	const int newNum = valeurA * valeurBden + valeurBnum; //On effectue l'opération Add
	const shared_ptr<LRational> newLit = LRational::makeLiteral(newNum, valeurBden); //On créé un const shared_ptr pour notre nouveau int
	Stack::getInstance().push(newLit); //On pous notre Literal sur la Stack.
}
/* Fin AddIntRational */
/* Début AddRationalInt */
AddRationalInt::AddRationalInt(){
	Add::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRationalInt si on recherche l'opérateur Add pour deux Int.
}
void AddRationalInt::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	AddIntRational::execution(B, A);
}
/* Fin AddRationalInt */
/* Début AddRationalRational */
AddRationalRational::AddRationalRational(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRationalRational si on recherche l'opérateur Add pour deux Int.
}
void AddRationalRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
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
	Stack::getInstance().push(newLit); //On pous notre Literal sur la Stack.
}
/* Fin AddRationalRational */
/* Début AddRealReal */
AddRealReal::AddRealReal(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRealReal si on recherche l'opérateur Add pour deux Int.
}
void AddRealReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LReal* lIntB = dynamic_cast<LReal*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurB = lIntB->getValue();
	const double newVal = valeurA + valeurB; //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	Stack::getInstance().push(newLit); //On pous notre Literal sur la Stack.
}
/* Fin AddRealReal */
/* Début AddRealRational */
AddRealRational::AddRealRational(){
	Add::get().addBehaviour(typeA, typeB, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRealRational si on recherche l'opérateur Add pour deux Int.
}
void AddRealRational::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	Literal* litA = A.get(); //On récupère un podoubleeur de Literal sur le shared_ptr
	Literal* litB = B.get();
	LReal* lIntA = dynamic_cast<LReal*>(litA); //On cast ce podoubleeur en LReal
	LRational* lIntB = dynamic_cast<LRational*>(litB);
	double valeurA = lIntA->getValue(); //On récupère la valeur de ce Literal
	double valeurBnum = lIntB->getNum();
	double valeurBden = lIntB->getDen();
	const double newVal = valeurA + (valeurBnum / valeurBden); //On effectue l'opération Add
	const shared_ptr<LReal> newLit = LReal::makeLiteral(newVal); //On créé un const shared_ptr pour notre nouveau double
	Stack::getInstance().push(newLit); //On pous notre Literal sur la Stack.
}
/* Fin AddRealRational */
/* Début AddRationalReal */
AddRationalReal::AddRationalReal(){
	Add::get().addBehaviour(typeB, typeA, this);  //On ajoute une entrée au Map de Add, qui permettra de trouver un objet de la classe AddRealInt si on recherche l'opérateur Add pour deux Int.
}
void AddRationalReal::execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B){
	AddRealRational::execution(B, A);
}
/* Fin AddRationalReal */
/* Fin Add */

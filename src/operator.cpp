/*
 * Operator.cpp
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */
#include <iostream>
#include <string>
#include <map>

#include "../include/operator.h"
#include "../include/unaryOperator.h"
#include "../include/binaryOperator.h"
#include "../include/ternaryOperator.h"
#include "../include/computer.h"
#include "../include/literal.h"

using namespace std;


unique_ptr<Operator> Operator::instance = nullptr;

std::map<std::string, shared_ptr<TypeOperator>> Operator::operators = {};

Operator& Operator::getInstance(){
	if(instance == nullptr)
		instance = unique_ptr<Operator>(new Operator);
	return *instance;
}

void Operator::freeInstance(){
	instance = nullptr;
}

void Operator::addOperator(std::string name, std::shared_ptr<TypeOperator> oper){
	operators.insert(std::make_pair(name, oper));
}

void Operator::delOperator(std::string name){
	if(operators.count(name))
		operators.erase(name);
}

bool Operator::isOperator(std::string s){
	return (operators.count(s) > 0);
}

TypeOperator& Operator::getOperator(std::string s){
	if(!isOperator(s)){
		throw OperatorException("Undefined operator");
	}
	return *operators.at(s);
}

int AbstractOperation::getValueInteger(const std::shared_ptr<Literal> A){
	Literal* lit = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	LInteger* lInt = dynamic_cast<LInteger*>(lit); //On cast ce pointeur en LInteger
	int valeur = lInt->getValue(); //On récupère la valeur de ce Literal
	return valeur;
}

double AbstractOperation::getValueReal(const std::shared_ptr<Literal> A){
	Literal* lit = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	LReal* lInt = dynamic_cast<LReal*>(lit); //On cast ce pointeur en LReal
	double valeur = lInt->getValue(); //On récupère la valeur de ce Literal
	return valeur;
}

std::pair<int, int> AbstractOperation::getValueRational(const std::shared_ptr<Literal> A){
	Literal* lit = A.get(); //On récupère un pointeur de Literal sur le shared_ptr
	LRational* lInt = dynamic_cast<LRational*>(lit); //On cast ce pointeur en LRational
	int num = lInt->getNum(); //On récupère le numérateur de ce Literal
	int den = lInt->getDen(); //On récupère le dénominateur de ce Literal
	return std::make_pair(num, den);
}

/* Définition de l'opérateur CLEAR */
shared_ptr<Clear> Clear::instance = nullptr;
bool Clear::apply(Stack& s){
	while(s.size() != 0){
		s.pop();
	}
	return true;
}

Clear& Clear::get(){
	if(instance == nullptr){
		instance = shared_ptr<Clear>(new Clear);
		Operator::addOperator(instance->name, instance);
	}
	return *instance;
}

void Clear::free(){
	if(instance != nullptr){
		Operator::delOperator(instance->name);
		instance = nullptr;
	}
}

/* fin opérateur CLEAR */
//shared_ptr<AddIntInt> addIntInt = make_shared<AddIntInt>();
void creationOperators(){
	Clear::get();

	shared_ptr<NegInt> negInt = make_shared<NegInt>();
	negInt->addMyself();
	shared_ptr<NegReal> negReal = make_shared<NegReal>();
	negReal->addMyself();
	shared_ptr<NegRational> negRational = make_shared<NegRational>();
	negRational->addMyself();

	Not::get();

	Dup::get();

	Drop::get();

    Eval::get();

    Ift::get();

    Ifte::get();

    Forget::get();

    Sto::get();

	shared_ptr<AddIntInt> addIntInt = make_shared<AddIntInt>();
	addIntInt->addMyself();
	shared_ptr<AddIntReal> addIntReal = make_shared<AddIntReal>();
	addIntReal->addMyself();
	shared_ptr<AddRealInt> addRealInt = make_shared<AddRealInt>();
	addRealInt->addMyself();
	shared_ptr<AddIntRational> addIntRational = make_shared<AddIntRational>();
	addIntRational->addMyself();
	shared_ptr<AddRationalInt> addRationalInt = make_shared<AddRationalInt>();
	addRationalInt->addMyself();
	shared_ptr<AddRationalRational> addRationalRational = make_shared<AddRationalRational>();
	addRationalRational->addMyself();
	shared_ptr<AddRealReal> addRealReal = make_shared<AddRealReal>();
	addRealReal->addMyself();
	shared_ptr<AddRealRational> addRealRational = make_shared<AddRealRational>();
	addRealRational->addMyself();
	shared_ptr<AddRationalReal> addRationalReal = make_shared<AddRationalReal>();
	addRationalReal->addMyself();

	shared_ptr<MulIntInt> mulIntInt = make_shared<MulIntInt>();
	mulIntInt->addMyself();
	shared_ptr<MulIntReal> mulIntReal = make_shared<MulIntReal>();
	mulIntReal->addMyself();
	shared_ptr<MulRealInt> mulRealInt = make_shared<MulRealInt>();
	mulRealInt->addMyself();
	shared_ptr<MulIntRational> mulIntRational = make_shared<MulIntRational>();
	mulIntRational->addMyself();
	shared_ptr<MulRationalInt> mulRationalInt = make_shared<MulRationalInt>();
	mulRationalInt->addMyself();
	shared_ptr<MulRationalRational> mulRationalRational = make_shared<MulRationalRational>();
	mulRationalRational->addMyself();
	shared_ptr<MulRealReal> mulRealReal = make_shared<MulRealReal>();
	mulRealReal->addMyself();
	shared_ptr<MulRealRational> mulRealRational = make_shared<MulRealRational>();
	mulRealRational->addMyself();
	shared_ptr<MulRationalReal> mulRationalReal = make_shared<MulRationalReal>();
	mulRationalReal->addMyself();

	shared_ptr<SubIntInt> subIntInt = make_shared<SubIntInt>();
	subIntInt->addMyself();
	shared_ptr<SubIntReal> subIntReal = make_shared<SubIntReal>();
	subIntReal->addMyself();
	shared_ptr<SubRealInt> subRealInt = make_shared<SubRealInt>();
	subRealInt->addMyself();
	shared_ptr<SubIntRational> subIntRational = make_shared<SubIntRational>();
	subIntRational->addMyself();
	shared_ptr<SubRationalInt> subRationalInt = make_shared<SubRationalInt>();
	subRationalInt->addMyself();
	shared_ptr<SubRationalRational> subRationalRational = make_shared<SubRationalRational>();
	subRationalRational->addMyself();
	shared_ptr<SubRealReal> subRealReal = make_shared<SubRealReal>();
	subRealReal->addMyself();
	shared_ptr<SubRealRational> subRealRational = make_shared<SubRealRational>();
	subRealRational->addMyself();
	shared_ptr<SubRationalReal> subRationalReal = make_shared<SubRationalReal>();
	subRationalReal->addMyself();

	shared_ptr<DivIntInt> divIntInt = make_shared<DivIntInt>();
	divIntInt->addMyself();
	shared_ptr<DivIntReal> divIntReal = make_shared<DivIntReal>();
	divIntReal->addMyself();
	shared_ptr<DivRealInt> divRealInt = make_shared<DivRealInt>();
	divRealInt->addMyself();
	shared_ptr<DivIntRational> divIntRational = make_shared<DivIntRational>();
	divIntRational->addMyself();
	shared_ptr<DivRationalInt> divRationalInt = make_shared<DivRationalInt>();
	divRationalInt->addMyself();
	shared_ptr<DivRationalRational> divRationalRational = make_shared<DivRationalRational>();
	divRationalRational->addMyself();
	shared_ptr<DivRealReal> divRealReal = make_shared<DivRealReal>();
	divRealReal->addMyself();
	shared_ptr<DivRealRational> divRealRational = make_shared<DivRealRational>();
	divRealRational->addMyself();
	shared_ptr<DivRationalReal> divRationalReal = make_shared<DivRationalReal>();
	divRationalReal->addMyself();

	shared_ptr<ModIntInt> modIntInt = make_shared<ModIntInt>();
	modIntInt->addMyself();

	shared_ptr<DivEIntInt> diveIntInt = make_shared<DivEIntInt>();
	diveIntInt->addMyself();

	shared_ptr<EquIntInt> equIntInt = make_shared<EquIntInt>();
	equIntInt->addMyself();
	shared_ptr<EquIntReal> equIntReal = make_shared<EquIntReal>();
	equIntReal->addMyself();
	shared_ptr<EquRealInt> equRealInt = make_shared<EquRealInt>();
	equRealInt->addMyself();
	shared_ptr<EquIntRational> equIntRational = make_shared<EquIntRational>();
	equIntRational->addMyself();
	shared_ptr<EquRationalInt> equRationalInt = make_shared<EquRationalInt>();
	equRationalInt->addMyself();
	shared_ptr<EquRationalRational> equRationalRational = make_shared<EquRationalRational>();
	equRationalRational->addMyself();
	shared_ptr<EquRealReal> equRealReal = make_shared<EquRealReal>();
	equRealReal->addMyself();
	shared_ptr<EquRealRational> equRealRational = make_shared<EquRealRational>();
	equRealRational->addMyself();
	shared_ptr<EquRationalReal> equRationalReal = make_shared<EquRationalReal>();
	equRationalReal->addMyself();

	shared_ptr<DifIntInt> difIntInt = make_shared<DifIntInt>();
	difIntInt->addMyself();
	shared_ptr<DifIntReal> difIntReal = make_shared<DifIntReal>();
	difIntReal->addMyself();
	shared_ptr<DifRealInt> difRealInt = make_shared<DifRealInt>();
	difRealInt->addMyself();
	shared_ptr<DifIntRational> difIntRational = make_shared<DifIntRational>();
	difIntRational->addMyself();
	shared_ptr<DifRationalInt> difRationalInt = make_shared<DifRationalInt>();
	difRationalInt->addMyself();
	shared_ptr<DifRationalRational> difRationalRational = make_shared<DifRationalRational>();
	difRationalRational->addMyself();
	shared_ptr<DifRealReal> difRealReal = make_shared<DifRealReal>();
	difRealReal->addMyself();
	shared_ptr<DifRealRational> difRealRational = make_shared<DifRealRational>();
	difRealRational->addMyself();
	shared_ptr<DifRationalReal> difRationalReal = make_shared<DifRationalReal>();
	difRationalReal->addMyself();

	shared_ptr<InfIntInt> infIntInt = make_shared<InfIntInt>();
	infIntInt->addMyself();
	shared_ptr<InfIntReal> infIntReal = make_shared<InfIntReal>();
	infIntReal->addMyself();
	shared_ptr<InfRealInt> infRealInt = make_shared<InfRealInt>();
	infRealInt->addMyself();
	shared_ptr<InfIntRational> infIntRational = make_shared<InfIntRational>();
	infIntRational->addMyself();
	shared_ptr<InfRationalInt> infRationalInt = make_shared<InfRationalInt>();
	infRationalInt->addMyself();
	shared_ptr<InfRationalRational> infRationalRational = make_shared<InfRationalRational>();
	infRationalRational->addMyself();
	shared_ptr<InfRealReal> infRealReal = make_shared<InfRealReal>();
	infRealReal->addMyself();
	shared_ptr<InfRealRational> infRealRational = make_shared<InfRealRational>();
	infRealRational->addMyself();
	shared_ptr<InfRationalReal> infRationalReal = make_shared<InfRationalReal>();
	infRationalReal->addMyself();

	shared_ptr<InfEquIntInt> infEquIntInt = make_shared<InfEquIntInt>();
	infEquIntInt->addMyself();
	shared_ptr<InfEquIntReal> infEquIntReal = make_shared<InfEquIntReal>();
	infEquIntReal->addMyself();
	shared_ptr<InfEquRealInt> infEquRealInt = make_shared<InfEquRealInt>();
	infEquRealInt->addMyself();
	shared_ptr<InfEquIntRational> infEquIntRational = make_shared<InfEquIntRational>();
	infEquIntRational->addMyself();
	shared_ptr<InfEquRationalInt> infEquRationalInt = make_shared<InfEquRationalInt>();
	infEquRationalInt->addMyself();
	shared_ptr<InfEquRationalRational> infEquRationalRational = make_shared<InfEquRationalRational>();
	infEquRationalRational->addMyself();
	shared_ptr<InfEquRealReal> infEquRealReal = make_shared<InfEquRealReal>();
	infEquRealReal->addMyself();
	shared_ptr<InfEquRealRational> infEquRealRational = make_shared<InfEquRealRational>();
	infEquRealRational->addMyself();
	shared_ptr<InfEquRationalReal> infEquRationalReal = make_shared<InfEquRationalReal>();
	infEquRationalReal->addMyself();

	shared_ptr<SupEquIntInt> supEquIntInt = make_shared<SupEquIntInt>();
	supEquIntInt->addMyself();
	shared_ptr<SupEquIntReal> supEquIntReal = make_shared<SupEquIntReal>();
	supEquIntReal->addMyself();
	shared_ptr<SupEquRealInt> supEquRealInt = make_shared<SupEquRealInt>();
	supEquRealInt->addMyself();
	shared_ptr<SupEquIntRational> supEquIntRational = make_shared<SupEquIntRational>();
	supEquIntRational->addMyself();
	shared_ptr<SupEquRationalInt> supEquRationalInt = make_shared<SupEquRationalInt>();
	supEquRationalInt->addMyself();
	shared_ptr<SupEquRationalRational> supEquRationalRational = make_shared<SupEquRationalRational>();
	supEquRationalRational->addMyself();
	shared_ptr<SupEquRealReal> supEquRealReal = make_shared<SupEquRealReal>();
	supEquRealReal->addMyself();
	shared_ptr<SupEquRealRational> supEquRealRational = make_shared<SupEquRealRational>();
	supEquRealRational->addMyself();
	shared_ptr<SupEquRationalReal> supEquRationalReal = make_shared<SupEquRationalReal>();
	supEquRationalReal->addMyself();

	shared_ptr<SupIntInt> supIntInt = make_shared<SupIntInt>();
	supIntInt->addMyself();
	shared_ptr<SupIntReal> supIntReal = make_shared<SupIntReal>();
	supIntReal->addMyself();
	shared_ptr<SupRealInt> supRealInt = make_shared<SupRealInt>();
	supRealInt->addMyself();
	shared_ptr<SupIntRational> supIntRational = make_shared<SupIntRational>();
	supIntRational->addMyself();
	shared_ptr<SupRationalInt> supRationalInt = make_shared<SupRationalInt>();
	supRationalInt->addMyself();
	shared_ptr<SupRationalRational> supRationalRational = make_shared<SupRationalRational>();
	supRationalRational->addMyself();
	shared_ptr<SupRealReal> supRealReal = make_shared<SupRealReal>();
	supRealReal->addMyself();
	shared_ptr<SupRealRational> supRealRational = make_shared<SupRealRational>();
	supRealRational->addMyself();
	shared_ptr<SupRationalReal> supRationalReal = make_shared<SupRationalReal>();
	supRationalReal->addMyself();

	And::get();

	Or::get();

	Swap::get();

}

void destructionOperators(){
	Clear::free();
	Neg::free();
	Not::get();
	Dup::get();
	Drop::get();
	Swap::get();
	Add::free();
	Mul::free();
	Sub::free();
	Div::free();
	Mod::free();;
	DivE::free();
	Equ::free();
	Dif::free();
	InfEqu::free();
	Inf::free();
	SupEqu::free();
	Sup::free();
	And::free();
	Or::free();
	Swap::free();

	Operator::freeInstance();
}

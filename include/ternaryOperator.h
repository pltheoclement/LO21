/*
 * ternaryOperator.h
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */

#ifndef HEADERS_TERNARYOPERATOR_H_
#define HEADERS_TERNARYOPERATOR_H_

#include <map>
#include <iostream>
#include <memory>

#include "computer.h"
#include "literal.h"
#include "operator.h"


class AbstractTernaryOperation : public AbstractOperation {
	LiteralType a;
	LiteralType b;
	LiteralType c;
public:
	AbstractTernaryOperation(LiteralType litA, LiteralType litB, LiteralType litC);
	virtual const std::shared_ptr<Literal> execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B, std::shared_ptr<Literal> C) = 0;
	virtual ~AbstractTernaryOperation() = default;
};


class TernaryOperator : public TypeOperator{
    std::map<std::tuple<LiteralType,LiteralType, LiteralType>, AbstractTernaryOperation*> possibles;

public :
    virtual ~TernaryOperator(){}
    TernaryOperator(){}
    void ajouterComportement(LiteralType A, LiteralType B, LiteralType C, AbstractTernaryOperation* a) { possibles[std::make_tuple(A, B, C)]=a; }
    bool apply(Stack& s);
};


#endif /* HEADERS_TERNARYOPERATOR_H_ */

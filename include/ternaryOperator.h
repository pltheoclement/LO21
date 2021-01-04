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

#include "../include/operator.h"
#include "../include/computer.h"
#include "../include/literal.h"


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

/*
 * Classe de l'opérateur IFT
 * permet l'execution d'un If Then
 */
class Ifte : public TernaryOperator {
protected:
	std::string name = "IFTE";
	static std::shared_ptr<Ifte> instance;
	Ifte() = default;
public:
	static Ifte& get();
	static void free();
	/*
	 * Méthode permettant l'éxécution de l'opérateur IFTE.
	 * La méthode dépile 3 littérales. La 1ere (i.e. le dernier dépilé) est un test logique (tout type de littérale pour un "Vrai", littérale entière 0 pour un "Faux".
	 * Si la valeur de ce test est vrai, la deuxième littérale est évalué sinon la troisieme littérale est évaluée. La deuxième et la troisième littérale doit donc être une expression (LExpression) ou un programme (LProgram)
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
	 */
	bool apply(Stack& s);
};


#endif /* HEADERS_TERNARYOPERATOR_H_ */

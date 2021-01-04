/*
 * Operator.h
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */

#ifndef HEADERS_UNARYOPERATOR_H_
#define HEADERS_UNARYOPERATOR_H_

#include <map>
#include <iostream>
#include <memory>

#include "computer.h"
#include "literal.h"
#include "operator.h"

/*
 * Classe abstraite de laquelle hérite tous les comportements d'opérateurs unaires.
 * Elle hérite publiquement de AbstractOperation et de enable_shared_from_this<AbstractUnaryOperation>, permettant ainsi de renvoyer le pointeur "this" sous forme de shared_ptr
 */
class AbstractUnaryOperation : public AbstractOperation, public std::enable_shared_from_this<AbstractUnaryOperation> {
protected:
	LiteralType typeA; //correspond au type de la littérale sur lequel va s'executer l'opérateur
public:
	//AbstractUnaryOperation() = default;
	AbstractUnaryOperation(LiteralType a) : typeA(a){}
	/*
	 * méthode executant le comportement de l'opérateur souhaité.
	 * @param pointeru intelligent (shared) contenat la littérale correspondant au type de littérale de ce comportement d'opérateur
	 * @return resultat de l'opération
	 */
	virtual const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A) = 0;
	virtual ~AbstractUnaryOperation() = default;
};

/*
 * classe mère des opérateurs unaires
 */
class UnaryOperator : public TypeOperator{
protected:
	std::map<LiteralType, std::shared_ptr<AbstractUnaryOperation>> possibles;
public :
    virtual ~UnaryOperator();
    UnaryOperator(){};
    /*
     * méthode permettant d'ajouter un comportement (en fonction du type de littérale) à l'opérateur souhaité.
     * @param le type de la littérale dont on doit ajouter le comportement
     * @param un pointeur intelligent (shared) contenant le comportement d'opérateur à ajouter
     */
    void addBehaviour(LiteralType A, std::shared_ptr<AbstractUnaryOperation> a);
    /*
     * Méthode permettant l'éxécution de l'opérateur cette méthode appelle le comprtement souhaité en fonction de l'opérateur dépilé
     * Si l'execution se passe bien elle empile le résultat de l'execution de l'opérateur sur la littérale en haut de la pile
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
     */
    bool apply(Stack& s);
};


/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur NEG.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractNeg : public AbstractUnaryOperation{
public:
	AbstractNeg() = default;
	~AbstractNeg() = default;
	AbstractNeg(LiteralType a):AbstractUnaryOperation(a){}
	void addMyself() override;
};

/*
 * Classe de l'opérateur NEG
 * Cette classe contient tous les comportements différents en fonction de l'opérateur souhaité
 * renvoit l'opposé de la littérale en haut de la pile
 */
class Neg : public UnaryOperator {
protected:
	std::string name = "NEG";
	static std::shared_ptr<Neg> instance;
	Neg() = default;
public:
	static Neg& get();
	static void free();
};

/*
 * Classe du comportement de l'opérateur NEG sur un entier
 */
class NegInt : public AbstractNeg{
public:
	/*
	 * méthode executant le comportement de l'opérateur Neg sur un entier.
	 * @param pointeur intelligent (shared) contenat un LInteger
	 * @return pointeur intelligent (shared) contenant un LInteger dont la valeur est l'opposée de celui en paramètre
	 */
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
	NegInt(): AbstractNeg(linteger){}
};

/*
 * Classe du comportement de l'opérateur NEG sur un réel
 */
class NegReal : public AbstractNeg{
public:
	/*
	 * méthode executant le comportement de l'opérateur Neg sur un réel.
	 * @param pointeur intelligent (shared) contenat un LReal
	 * @return pointeur intelligent (shared) contenant un LReal dont la valeur est l'opposée de celui en paramètre
	 */
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
	NegReal(): AbstractNeg(lreal){}
};

/*
 * Classe du comportement de l'opérateur NEG sur un rationnel
 */
class NegRational : public AbstractNeg{
public:
	/*
	 * méthode executant le comportement de l'opérateur Neg sur un rationnel.
	 * @param pointeur intelligent (shared) contenat un LRational
	 * @return pointeur intelligent (shared) contenant un LRational dont la valeur est l'opposée de celui en paramètre
	 */
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A);
	NegRational(): AbstractNeg(lrational){}
};



/*
 * Classe de l'opérateur NOT
 * renvoit un non logique
 */
class Not : public UnaryOperator {
protected:
	std::string name = "NOT";
	static std::shared_ptr<Not> instance;
	Not() = default;
public:
	static Not& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur NOT.
     * Si l'execution se passe bien elle empile le résultat d'un NON logique sur le littérale en haut de la pile
     * la littérale entière (LInteger) 1 correspond à un Vrai, la littérale entière (LInteger) 0 correspond à un Faux
     *
     * Toute littérale qui n'est pas la littérale entière 0 est considérée comme étant vraie
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
     */
	bool apply(Stack& s);
};

/*
 * Classe de l'opérateur EVAL
 */
class Eval : public UnaryOperator {
protected:
	std::string name = "EVAL";
	static std::shared_ptr<Eval> instance;
	Eval() = default;
public:
	static Eval& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur EVAL.
     * Sur une littérale expression (LExpression) elle renvoit la valeur contenue dans la variable du nom de cette expression (Littérale ou programme)
     * Sur une littérale programme, elle execute le programme en question.
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
     */
	bool apply(Stack& s);

};

/*
 * Classe de l'opérateur DUP qui dupplique l'opérateur en haut de la pile
 */
class Dup : public UnaryOperator {
protected:
	std::string name = "DUP";
	static std::shared_ptr<Dup> instance;
	Dup() = default;
public:
	static Dup& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur DUP.
     * Si l'opération s'execute correctement, elle empile une copie de la littérale en haut de la pile
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
     */
	bool apply(Stack& s);
};

/*
 * Classe de l'opérateur DUP qui supprime de la pile la littérale en haut de la pile
 */
class Drop : public UnaryOperator {
protected:
	std::string name = "DROP";
	static std::shared_ptr<Drop> instance;
	Drop() = default;
public:
	static Drop& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur DROP.
     * Si l'opération s'execute correctement, elle duplique la littérale en haut de la pile
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
     */
	bool apply(Stack& s);
};

/*
 * Classe de l'opérateur FORGET qui oublie la valeur d'une variable
 */
class Forget : public UnaryOperator {
protected:
	std::string name = "FORGET";
	static std::shared_ptr<Forget> instance;
	Forget() = default;
public:
	static Forget& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur FORGET.
     * Si l'opération s'execute correctement, elle récupère le nom de la variable en haut de la pile et délie le nom de la variable et la variable. (cette varaible est donc oubliée)
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
     */
	bool apply(Stack& s);
};

#endif

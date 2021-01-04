/*
 * binaryOperator.h
 *
 *  Created on: Dec 15, 2020
 *      Author: theo
 */

#ifndef HEADERS_BINARYOPERATOR_H_
#define HEADERS_BINARYOPERATOR_H_

#include <map>
#include <iostream>
#include <memory>

#include "computer.h"
#include "literal.h"
#include "operator.h"

/*
 * Classe abstraite de laquelle hérite tous les comportements d'opérateurs binaires.
 * Elle hérite publiquement de AbstractOperation et de enable_shared_from_this<AbstractUnaryOperation>, permettant ainsi de renvoyer le pointeur "this" sous forme de shared_ptr
 */
class AbstractBinaryOperation : public AbstractOperation, public std::enable_shared_from_this<AbstractBinaryOperation> {
protected:
	LiteralType typeA; //correspond au type de la premiere littérale sur laquel va s'executer l'opérateur
	LiteralType typeB; //correspond au type de la deuxième littérale sur laquel va s'executer l'opérateur
public:
    AbstractBinaryOperation() = default;
	AbstractBinaryOperation(LiteralType a, LiteralType b) : typeA(a), typeB(b){}
	virtual const std::shared_ptr<Literal> execution(std::shared_ptr<Literal> A, std::shared_ptr<Literal> B) = 0;
	virtual ~AbstractBinaryOperation() = default;

};

/*
 * classe mère des opérateurs binaire
 */
class BinaryOperator : public TypeOperator{
protected:
    std::map<std::pair<LiteralType,LiteralType>, std::shared_ptr<AbstractBinaryOperation>> possibles;

public :
    virtual ~BinaryOperator(){};
    BinaryOperator(){};
    void addBehaviour(LiteralType A, LiteralType B, std::shared_ptr<AbstractBinaryOperation> a);
    bool apply(Stack& s);
};

/*
 * Classe de l'opérateur Add, premettant l'ajout de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les additionne (en fonction de leur type) et empile le resultat
 */
class Add : public BinaryOperator {
protected:
	std::string name = "+";
	static std::shared_ptr<Add> instance;
	Add() = default;
public:
	static Add& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Add.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractAdd : public AbstractBinaryOperation{
public:
	AbstractAdd() = default;
	AbstractAdd(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	~AbstractAdd() = default;
	void addMyself() override;
};

class AddIntInt : public AbstractAdd{
public:
	AddIntInt(): AbstractAdd(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntReal : public AbstractAdd{
public:
	AddIntReal(): AbstractAdd(linteger, lreal){}
	AddIntReal(LiteralType a, LiteralType b):AbstractAdd(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealInt : public AddIntReal{
public:
	AddRealInt(): AddIntReal(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddIntRational : public AbstractAdd{
public:
	AddIntRational(): AbstractAdd(linteger, lrational){}
	AddIntRational(LiteralType a, LiteralType b):AbstractAdd(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalInt : public AddIntRational{
public:
	AddRationalInt(): AddIntRational(lrational, linteger){}

	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalRational : public AbstractAdd{
public:
	AddRationalRational(): AbstractAdd(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealReal : public AbstractAdd{
public:
	AddRealReal(): AbstractAdd(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRealRational : public AbstractAdd{
public:
	AddRealRational(): AbstractAdd(lreal, lrational){}
	AddRealRational(LiteralType a, LiteralType b):AbstractAdd(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class AddRationalReal : public AddRealRational{
public:
	AddRationalReal(): AddRealRational(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur Mul, premettant la multiplication de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les multiplie (en fonction de leur type) et empile le resultat
 */
class Mul : public BinaryOperator {
protected:
	std::string name = "*";
	static std::shared_ptr<Mul> instance;
	Mul() = default;
public:
	static Mul& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Mul.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractMul : public AbstractBinaryOperation{
public:
	AbstractMul() = default;
	~AbstractMul() = default;
	AbstractMul(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class MulIntInt : public AbstractMul{
public:
	MulIntInt(): AbstractMul(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntReal : public AbstractMul{
public:
	MulIntReal(): AbstractMul(linteger, lreal){}
	MulIntReal(LiteralType a, LiteralType b):AbstractMul(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealInt : public MulIntReal{
public:
	MulRealInt(): MulIntReal(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulIntRational : public AbstractMul{
public:
	MulIntRational(): AbstractMul(linteger, lrational){}
	MulIntRational(LiteralType a, LiteralType b):AbstractMul(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalInt : public MulIntRational{
public:
	MulRationalInt(): MulIntRational(lrational, linteger){}

	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalRational : public AbstractMul{
public:
	MulRationalRational(): AbstractMul(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealReal : public AbstractMul{
public:
	MulRealReal(): AbstractMul(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRealRational : public AbstractMul{
public:
	MulRealRational(): AbstractMul(lreal, lrational){}
	MulRealRational(LiteralType a, LiteralType b):AbstractMul(a, b){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class MulRationalReal : public MulRealRational{
public:
	MulRationalReal(): MulRealRational(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur Sub, premettant la soustraction de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les soustrait (en fonction de leur type) et empile le resultat
 */
class Sub : public BinaryOperator {
protected:
	std::string name = "-";
	static std::shared_ptr<Sub> instance;
	Sub() = default;
public:
	static Sub& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Sub.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractSub : public AbstractBinaryOperation{
public:
	AbstractSub() = default;
	~AbstractSub() = default;
	AbstractSub(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class SubIntInt : public AbstractSub{
public:
	SubIntInt(): AbstractSub(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntReal : public AbstractSub{
public:
	SubIntReal(): AbstractSub(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealInt : public AbstractSub{
public:
	SubRealInt(): AbstractSub(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubIntRational : public AbstractSub{
public:
	SubIntRational(): AbstractSub(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalInt : public AbstractSub{
public:
	SubRationalInt(): AbstractSub(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalRational : public AbstractSub{
public:
	SubRationalRational(): AbstractSub(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealReal : public AbstractSub{
public:
	SubRealReal(): AbstractSub(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRealRational : public AbstractSub{
public:
	SubRealRational(): AbstractSub(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SubRationalReal : public AbstractSub{
public:
	SubRationalReal(): AbstractSub(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur Div, premettant la division de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les divise (en fonction de leur type) et empile le resultat
 * le cas de la division par 0 renvoit une exeption de type OperatorException
 */
class Div : public BinaryOperator {
protected:
	std::string name = "/";
	static std::shared_ptr<Div> instance;
	Div() = default;
public:
	static Div& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Div.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractDiv : public AbstractBinaryOperation{
public:
	AbstractDiv() = default;
	~AbstractDiv() = default;
	AbstractDiv(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class DivIntInt : public AbstractDiv{
public:
	DivIntInt(): AbstractDiv(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntReal : public AbstractDiv{
public:
	DivIntReal(): AbstractDiv(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealInt : public AbstractDiv{
public:
	DivRealInt(): AbstractDiv(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivIntRational : public AbstractDiv{
public:
	DivIntRational(): AbstractDiv(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalInt : public AbstractDiv{
public:
	DivRationalInt(): AbstractDiv(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalRational : public AbstractDiv{
public:
	DivRationalRational(): AbstractDiv(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealReal : public AbstractDiv{
public:
	DivRealReal(): AbstractDiv(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRealRational : public AbstractDiv{
public:
	DivRealRational(): AbstractDiv(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DivRationalReal : public AbstractDiv{
public:
	DivRationalReal(): AbstractDiv(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur Mod, premettant le modulo de deux littérales entières
 * Lors de son appel (par la méthode apply) dépile 2 littérales entières et réaluse le modulo de l'une sur l'autre et empile le resultat
 * le cas de la division par 0 renvoit une exeption de type OperatorException
 */
class Mod : public BinaryOperator {
protected:
	std::string name = "MOD";
	static std::shared_ptr<Mod> instance;
	Mod() = default;
public:
	static Mod& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Mod.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractMod : public AbstractBinaryOperation{
public:
	AbstractMod() = default;
	~AbstractMod() = default;
	AbstractMod(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class ModIntInt : public AbstractMod{
public:
	ModIntInt(): AbstractMod(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur DivE, premettant la division entière de deux littérales entières
 * Lors de son appel (par la méthode apply) dépile 2 littérales entières et les divise (en fonction de leur type) et empile le resultat entier
 * le cas de la division par 0 renvoit une exeption de type OperatorException
 */
class DivE : public BinaryOperator {
protected:
	std::string name = "DIV";
	static std::shared_ptr<DivE> instance;
	DivE() = default;
public:
	static DivE& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur DivE.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstarctDivE : public AbstractBinaryOperation{
public:
	AbstarctDivE() = default;
	~AbstarctDivE() = default;
	AbstarctDivE(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class DivEIntInt : public AbstarctDivE{
public:
	DivEIntInt(): AbstarctDivE(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur Equ, premettant la comparaison d'égalité de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les compare (en fonction de leur type)
 * elle empile la litttérale entière 1 si les deux littérales sont égales, la littérale entière 0 sinon.
 */
class Equ : public BinaryOperator {
protected:
	std::string name = "=";
	static std::shared_ptr<Equ> instance;
	Equ() = default;
public:
	static Equ& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Equ.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractEqu : public AbstractBinaryOperation{
public:
	AbstractEqu() = default;
	~AbstractEqu() = default;
	AbstractEqu(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class EquIntInt : public AbstractEqu{
public:
	EquIntInt(): AbstractEqu(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquIntReal : public AbstractEqu{
public:
	EquIntReal(): AbstractEqu(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealInt : public AbstractEqu{
public:
	EquRealInt(): AbstractEqu(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquIntRational : public AbstractEqu{
public:
	EquIntRational(): AbstractEqu(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalInt : public AbstractEqu{
public:
	EquRationalInt(): AbstractEqu(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalRational : public AbstractEqu{
public:
	EquRationalRational(): AbstractEqu(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealReal : public AbstractEqu{
public:
	EquRealReal(): AbstractEqu(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRealRational : public AbstractEqu{
public:
	EquRealRational(): AbstractEqu(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class EquRationalReal : public AbstractEqu{
public:
	EquRationalReal(): AbstractEqu(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur Dif, premettant la comparaison d'inégalité de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les compare (en fonction de leur type)
 * elle empile la litttérale entière 0 si les deux littérales sont égales, la littérale entière 1 sinon.
 */
class Dif : public BinaryOperator {
protected:
	std::string name = "!=";
	static std::shared_ptr<Dif> instance;
	Dif() = default;
public:
	static Dif& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Dif.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractDif : public AbstractBinaryOperation{
public:
	AbstractDif() = default;
	~AbstractDif() = default;
	AbstractDif(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class DifIntInt : public AbstractDif{
public:
	DifIntInt(): AbstractDif(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifIntReal : public AbstractDif{
public:
	DifIntReal(): AbstractDif(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealInt : public AbstractDif{
public:
	DifRealInt(): AbstractDif(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifIntRational : public AbstractDif{
public:
	DifIntRational(): AbstractDif(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalInt : public AbstractDif{
public:
	DifRationalInt(): AbstractDif(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalRational : public AbstractDif{
public:
	DifRationalRational(): AbstractDif(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealReal : public AbstractDif{
public:
	DifRealReal(): AbstractDif(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRealRational : public AbstractDif{
public:
	DifRealRational(): AbstractDif(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class DifRationalReal : public AbstractDif{
public:
	DifRationalReal(): AbstractDif(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur InfEqu, premettant la comparaison d'infériorité (et égalité) de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les compare (en fonction de leur type)
 * elle empile la litttérale entière 1 si la littérale en deuxième position (par rapport au haut de la pile) est inférieure ou égale à la littérale en premiere position.
 */
class InfEqu : public BinaryOperator {
protected:
	std::string name = "=<";
	static std::shared_ptr<InfEqu> instance;
	InfEqu() = default;
public:
	static InfEqu& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur InfEqu.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractInfEqu : public AbstractBinaryOperation{
public:
	AbstractInfEqu() = default;
	~AbstractInfEqu() = default;
	AbstractInfEqu(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class InfEquIntInt : public AbstractInfEqu{
public:
	InfEquIntInt(): AbstractInfEqu(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquIntReal : public AbstractInfEqu{
public:
	InfEquIntReal(): AbstractInfEqu(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealInt : public AbstractInfEqu{
public:
	InfEquRealInt(): AbstractInfEqu(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquIntRational : public AbstractInfEqu{
public:
	InfEquIntRational(): AbstractInfEqu(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalInt : public AbstractInfEqu{
public:
	InfEquRationalInt(): AbstractInfEqu(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalRational : public AbstractInfEqu{
public:
	InfEquRationalRational(): AbstractInfEqu(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealReal : public AbstractInfEqu{
public:
	InfEquRealReal(): AbstractInfEqu(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRealRational : public AbstractInfEqu{
public:
	InfEquRealRational(): AbstractInfEqu(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfEquRationalReal : public AbstractInfEqu{
public:
	InfEquRationalReal(): AbstractInfEqu(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur Inf, premettant la comparaison d'infériorité de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les compare (en fonction de leur type)
 * elle empile la litttérale entière 1 si la littérale en deuxième position (par rapport au haut de la pile) est inférieure à la littérale en premiere position.
 */
class Inf : public BinaryOperator {
protected:
	std::string name = "<";
	static std::shared_ptr<Inf> instance;
	Inf() = default;
public:
	static Inf& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Inf.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractInf : public AbstractBinaryOperation{
public:
	AbstractInf() = default;
	AbstractInf(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	~AbstractInf() = default;
	void addMyself() override;
};

class InfIntInt : public AbstractInf{
public:
	InfIntInt(): AbstractInf(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfIntReal : public AbstractInf{
public:
	InfIntReal(): AbstractInf(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealInt : public AbstractInf{
public:
	InfRealInt(): AbstractInf(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfIntRational : public AbstractInf{
public:
	InfIntRational(): AbstractInf(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalInt : public AbstractInf{
public:
	InfRationalInt(): AbstractInf(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalRational : public AbstractInf{
public:
	InfRationalRational(): AbstractInf(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealReal : public AbstractInf{
public:
	InfRealReal(): AbstractInf(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRealRational : public AbstractInf{
public:
	InfRealRational(): AbstractInf(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class InfRationalReal : public AbstractInf{
public:
	InfRationalReal(): AbstractInf(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur SupEqu, premettant la comparaison de supériorité (et d'égalité) de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les compare (en fonction de leur type)
 * elle empile la litttérale entière 1 si la littérale en deuxième position (par rapport au haut de la pile) est supérieure ou égale à la littérale en premiere position.
 */
class SupEqu : public BinaryOperator {
protected:
	std::string name = ">=";
	static std::shared_ptr<SupEqu> instance;
	SupEqu() = default;
public:
	static SupEqu& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur SupEqu.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractSupEqu : public AbstractBinaryOperation{
public:
	AbstractSupEqu() = default;
	~AbstractSupEqu() = default;
	AbstractSupEqu(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class SupEquIntInt : public AbstractSupEqu{
public:
	SupEquIntInt(): AbstractSupEqu(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquIntReal : public AbstractSupEqu{
public:
	SupEquIntReal(): AbstractSupEqu(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealInt : public AbstractSupEqu{
public:
	SupEquRealInt(): AbstractSupEqu(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquIntRational : public AbstractSupEqu{
public:
	SupEquIntRational(): AbstractSupEqu(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalInt : public AbstractSupEqu{
public:
	SupEquRationalInt(): AbstractSupEqu(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalRational : public AbstractSupEqu{
public:
	SupEquRationalRational(): AbstractSupEqu(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealReal : public AbstractSupEqu{
public:
	SupEquRealReal(): AbstractSupEqu(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRealRational : public AbstractSupEqu{
public:
	SupEquRealRational(): AbstractSupEqu(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupEquRationalReal : public AbstractSupEqu{
public:
	SupEquRationalReal(): AbstractSupEqu(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur Sup, premettant la comparaison de supériorité de deux littérales
 * Lors de son appel (par la méthode apply) dépile 2 littérales et les compare (en fonction de leur type)
 * elle empile la litttérale entière 1 si la littérale en deuxième position (par rapport au haut de la pile) est supérieure à la littérale en premiere position.
 */
class Sup : public BinaryOperator {
protected:
	std::string name = ">";
	static std::shared_ptr<Sup> instance;
	Sup() = default;
public:
	static Sup& get();
	static void free();
};

/*
 * Classe abstraite de laquelle hérite tous les comportements de l'opérateur Sup.
 * Elle hérite publiquement de AbstractUnaryOperation
 */
class AbstractSup : public AbstractBinaryOperation{
public:
	AbstractSup() = default;
	~AbstractSup() = default;
	AbstractSup(LiteralType a, LiteralType b):AbstractBinaryOperation(a, b){}
	void addMyself() override;
};

class SupIntInt : public AbstractSup{
public:
	SupIntInt(): AbstractSup(linteger, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupIntReal : public AbstractSup{
public:
	SupIntReal(): AbstractSup(linteger, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealInt : public AbstractSup{
public:
	SupRealInt(): AbstractSup(lreal, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupIntRational : public AbstractSup{
public:
	SupIntRational(): AbstractSup(linteger, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalInt : public AbstractSup{
public:
	SupRationalInt(): AbstractSup(lrational, linteger){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalRational : public AbstractSup{
public:
	SupRationalRational(): AbstractSup(lrational, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealReal : public AbstractSup{
public:
	SupRealReal(): AbstractSup(lreal, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRealRational : public AbstractSup{
public:
	SupRealRational(): AbstractSup(lreal, lrational){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

class SupRationalReal : public AbstractSup{
public:
	SupRationalReal(): AbstractSup(lrational, lreal){}
	const std::shared_ptr<Literal> execution(const std::shared_ptr<Literal> A, const std::shared_ptr<Literal> B);
};

/*
 * Classe de l'opérateur And
 * renvoit un ET logique
 */
class And : public BinaryOperator {
protected:
	std::string name = "AND";
	static std::shared_ptr<And> instance;
	And() = default;
public:
	static And& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur AND.
     * Si l'execution se passe bien elle empile le résultat d'un ET logique etre les deux littérales au sommet de la pile
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
 * Classe de l'opérateur Or
 * renvoit un OU logique
 */
class Or : public BinaryOperator {
protected:
	std::string name = "OR";
	static std::shared_ptr<Or> instance;
	Or() = default;
public:
	static Or& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur OR.
     * Si l'execution se passe bien elle empile le résultat d'un OU logique etre les deux littérales au sommet de la pile
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
 * Classe de l'opérateur Swap
 * écahnge les positions des deux littérales au sommet de la pile
 */
class Swap : public BinaryOperator {
protected:
	std::string name = "SWAP";
	static std::shared_ptr<Swap> instance;
	Swap() = default;
public:
	static Swap& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur Swap.
     *Elle échange les positions des deux littérales au sommet de la pile
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
     */
	bool apply(Stack& s);
};

/*
 * Classe de l'opérateur Sto
 * permet de stocker une littérale dans une variable
 */
class Sto : public BinaryOperator {
protected:
	std::string name = "STO";
	static std::shared_ptr<Sto> instance;
	Sto() = default;
public:
	static Sto& get();
	static void free();
    /*
     * Méthode permettant l'éxécution de l'opérateur Sto.
     * Elle permet de stocker une littérale dans une variable.
     * La littérale au sommet de la pile doit être la littérale à stocker, la littérale suivante est une littérale expression du nom de la variable à stocker.
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
     */
	bool apply(Stack& s);
};

/*
 * Classe de l'opérateur IFT
 * permet l'execution d'un If Then
 */
class Ift : public BinaryOperator {
protected:
	std::string name = "IFT";
	static std::shared_ptr<Ift> instance;
	Ift() = default;
public:
	static Ift& get();
	static void free();
	/*
	 * Méthode permettant l'éxécution de l'opérateur IFT.
	 * La méthode dépile 2 littérales. La 1ere (i.e. le dernier dépilé) est un test logique (tout type de littérale pour un "Vrai", littérale entière 0 pour un "Faux".
	 * Si la valeur de ce test est vrai, la deuxième littérale est évalué sinon elle est abandonnée. La deuxième littérale doit donc être une expression (LExpression) ou un programme (LProgram)
     *
     * @param La pile sur laquelle l'opérateur s'applique
     *
     * @return true si l'opérateur à pu s'executer correctement, false sinon
	 */
	bool apply(Stack& s);
};


#endif /* HEADERS_BINARYOPERATOR_H_ */

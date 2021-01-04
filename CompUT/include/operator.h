/*
 * Operator.h
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */

#ifndef HEADERS_OPERATOR_H_
#define HEADERS_OPERATOR_H_

#include <map>
#include <iostream>
#include <memory>

#include "computer.h"
#include "literal.h"

/*
 * OperatorException est une classe d'exceptions,
 * Pour tout problème d'opération (division par 0 par exemple)
 * une OperatorException est levée
 */
class OperatorException {
	std::string info;
public:
	/*
	 * Constructeur de la classe OperatorException
	 *
	 * @param message d'erreur.
	 */
	OperatorException(const std::string& str): info(str){}
	/*
	 * Methode qui renvoit le message d'erreur
	 *
	 * @return message d'erreur
	 */
	std::string getInfo() const { return info; }
};

/*
 * La classe AbstractOperation est au sommet de la hiérarchie des classes gérant les comportements des opérateur en fonction des types de littérales
 * Elle possèdes des méthodes permettant d'éccéder à la valeur d'un litérale en lui fournissant un pointeur intelligent de cete littérale
 */
class AbstractOperation {
public:
	/*
	 * Méthode permettant d'ajouter ce comportement au map d'un opérateur
	 */
	virtual void addMyself() = 0;
	virtual ~AbstractOperation() = default;
	/*
	 * Méthode permettant d'accéder à la valeur contenue dans un poiteur intelligent de type Literal, dans lequel est stocké un LInteger
	 * renvoit une erreur si c'est un autre type de Literal
	 *
	 * @param Pointeur intelligent dans lequel est stocké un LInteger
	 * @return valeur du LInteger
	 */
	int getValueInteger(const std::shared_ptr<Literal> A);
	/*
	 * Méthode permettant d'accéder à la valeur contenue dans un poiteur intelligent de type Literal, dans lequel est stocké un LReal
	 * renvoit une erreur si c'est un autre type de Literal
	 *
	 * @param Pointeur intelligent dans lequel est stocké un LReal
	 * @return valeur du LReal
	 */
	double getValueReal(const std::shared_ptr<Literal> A);
	/*
	 * Méthode permettant d'accéder au numérateur et dénominateur de la valeur contenue dans un poiteur intelligent de type Literal, dans lequel est stocké un LRational
	 * renvoit une erreur si c'est un autre type de Literal
	 *
	 * @param Pointeur intelligent dans lequel est stocké un LRational
	 * @return pair contenant le numérateur en premiere position et le dénominateur en seconde position
	 */
	std::pair<int, int> getValueRational(const std::shared_ptr<Literal> A);
};

/*
 * classe mère de la hiérachie des opérateurs
 */
class TypeOperator {
protected:
	std::string name; //Nom de l'opérateur : correspond aussi à la commande à entrer dans l'application pour appeler l'opérateur
public:
	/*
	 * Méthode permettant l'éxécution de l'opérateur appelé
	 * s'il y a une erreur d'execution, la méthode laisse la pile intacte.
	 *
	 * @param La pile sur laquelle l'opérateur s'applique
	 *
	 * @return true si l'opérateur à pu s'executer correctement, false sinon
	 */
	virtual bool apply(Stack& s) = 0;
	virtual ~TypeOperator() = default;
};

/*
 * Opérateur permettant de vider la pile
 * Singleton
 */
class Clear : public TypeOperator {
	std::string name = "CLEAR";
	static std::shared_ptr<Clear> instance;
	Clear() = default;
public:
	/*
	 * Méthode permettant l'éxécution de l'opérateur
	 * Si l'execution se passe bien la pile est vide après l'appel de la méthode
	 *
	 * @param La pile sur laquelle l'opérateur s'applique
	 *
	 * @return true si l'opérateur à pu s'executer correctement, false sinon
	 */
	bool apply(Stack& s);
	static Clear& get();
	static void free();
};

/*
 * Classe permettant d'indexer tous les opérateur.
 */
class Operator{
	static std::map<std::string, std::shared_ptr<TypeOperator>> operators;
	static std::unique_ptr<Operator> instance;
	Operator() = default;

public:
	/*
	 * Méthode permettant de savoir si une chaîne de caractère correspond à un opérateur défini.
	 * @param chaine de caractère correspondant au nom d'un opérateur
	 * @return true si l'opérateur est défini, false sinon
	 */
	static bool isOperator(std::string s);
	/*
	 * Méthode permettant de renvoyer un opérateur en lui donnat son nom.
	 * renvoit une erreur si la chaine de caractère ne correpsond pas au nom d'un opérateur.
	 * @param chaine de caractère correspondant au nom d'un opérateur
	 * @return opérateur correspondant au nom de la chaine de carractère
	 */
	static TypeOperator& getOperator(std::string s);
	/*
	 * Méthode permettant d'ajouter un opérateur à la liste des opérateur définis.
	 * @param chaine de caractère correspondant au nom de l'opérateur et pointeur intelligent (shared) pointant sur l'opérateur à ajouter
	 */
	static void addOperator(std::string name, std::shared_ptr<TypeOperator> o);
	/*
	 * Méthode permettant de supprimer un opérateur à la liste des opérateur définis.
	 * @param chaine de caractère correspondant au nom de l'opérateur à supprimer
	 */
	static void delOperator(std::string name);
	/*
	 * Méthode permettant d'accéder au singleton Operator
	 */
	static Operator& getInstance();
	static void freeInstance();

};

/*
 * Fonction appelant une première fois tous les opérateurs ainsi que leurs différents comportement pour les initialiser une première fois avant leur utilisation.
 */
void creationOperators();
/*
 * Fonction permettant la destruction de tous les opérateurs.
 */
void destructionOperators();

#endif /* HEADERS_OPERATOR_H_ */

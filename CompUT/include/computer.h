#ifndef COMPUTER_H
#define COMPUTER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "literal.h"

/**
 * Pile de littérales
 *
 * Permet de stocker, d'empiler et de dépiler des littérales.
 */
class Stack{
    std::vector<std::shared_ptr<Literal>> storage;
    Stack() = default;
public:
    /**
     * Obtenir l'instance de la pile.
     * @return une référence vers l'instance de la pile.
     */
    static Stack& getInstance();

    /**
     * Itérer sur les valeurs de la pile.
     * @return un itérateur inverse sur les littérales de la pile.
     */
    std::vector<std::shared_ptr<Literal>>::const_reverse_iterator iterator() const;

    /**
     * Itérateur de fin
     * @return la condition de fin de l'itérateur inverse.
     */
    std::vector<std::shared_ptr<Literal>>::const_reverse_iterator end() const;

    /**
     * Ajouter une littérale au sommet de la pile.
     * @param pl un shared_ptr sur une littérale.
     */
    void push(const std::shared_ptr<Literal>& pl);

    /**
     * Supprimer la littérale du sommet de la pile.
     */
    void pop();

    /**
     * Accéder à la littérale du sommet de la pile.
     * @return un shared_ptr sur la littérale du sommet de la pile.
     */
    const std::shared_ptr<Literal>& top() const;

    /**
     * Obtenir la taille de la pile.
     * @return le nombre d'éléments présents dans la pile.
     */
    size_t size() const;
};

/**
 * Ordinateur logique
 *
 * Gère les variables, la sauvegarde, les messages et l'évaluation des entrées utilisateur.
 * Est un Singleton.
 */
class Computer{
    std::map<std::string, std::string> variables;
    std::string message = "Welcome";
    Computer() = default;
public:
    /**
     * Obtenir l'instance de l'ordinateur.
     * @return une référence vers l'instance de l'ordinateur.
     */
    static Computer& getInstance();

    /**
     * Obtenir le message d'erreur
     * @return le dernier message d'erreur
     */
    std::string getMessage() const;

    /**
     * Ajouter une variable ou un programme
     * @param name le nom de la variable ou du programme à stocker
     * @param l la littérale à stocker
     */
    void storeVariable(const std::string& name, const Literal& l);

    /**
     * Supprimer une variable ou un programme
     * @param name le nom de la variable ou du programme à supprimer
     */
    void forgetVariable(const std::string& name);

    /**
     * Empiler une variable ou évaluer un programme stocké
     * @param name le nom de la variable ou du programme
     */
    void pushVariable(const std::string& name);

    /**
     * Obtenir la représentation sous forme de chaîne de caractères d'une variable ou d'un programme
     * @param name le nom de la variable ou du programme enregistré
     * @return sa représentation en chaîne de caractères
     */
    std::string getVariable(const std::string& name);

    /**
     * Obtenir la liste des noms de toutes les variables
     * @return une liste de chaînes de caractères correspondant aux noms des variables
     */
    std::vector<std::string> getVariableNames() const;

    /**
     * Enregistrer l'état actuel dans un fichier
     * @param filename le nom du fichier
     */
    void saveToFile(const std::string& filename) const;

    /**
     * Charger un état depuis un fichier
     * @param filename le nom du fichier
     */
    void loadFromFile(const std::string& filename);

    /**
     * Evaluer une entrée utilisateur
     * @param s l'entrée à évaluer
     * @return la chaîne de caractères à réafficher à l'utilisateur en cas d'erreur
     */
    std::string evalLine(const std::string& s);
};
#endif

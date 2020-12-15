/*
 * Stack.h
 *
 *  Created on: Nov 22, 2020
 *      Author: theo
 */

#ifndef HEADERS_STACK_H_
#define HEADERS_STACK_H_

#include <memory>
#include "literal.h"

#include "literal.h"

class Stack{
    std::vector<std::shared_ptr<Literal>> storage;
    Stack() = default;
public:
    static Stack& getInstance(){}
    void push(const std::shared_ptr<Literal>& pl){}
    void pop(){}
    bool isEmpty(){}
    const std::shared_ptr<Literal>& top() const{}
    size_t size() const;
};

class Computer{
    std::map<std::string, std::string> variables;
    std::string message;
    Computer() = default;
public:
    static Computer& getInstance();
    void storeVariable(const std::string& name, const Literal& l);
    void forgetVariable(const std::string& name);
    void pushVariable(const std::string& name);
    std::string evalLine(const std::string& s);
};



#endif /* HEADERS_STACK_H_ */

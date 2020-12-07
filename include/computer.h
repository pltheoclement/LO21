#ifndef COMPUTER_H
#define COMPUTER_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "literal.h"

class Stack{
    std::vector<std::shared_ptr<Literal>> storage;
public:
    Stack() = default;
    void push(const std::shared_ptr<Literal>& pl);
    void pop();
    const std::shared_ptr<Literal>& top() const;
    size_t size() const;
};

class Computer{
    static Computer *instance;
    std::map<std::string, std::string> variables;
    std::string message;
    Stack stack;
    Computer() = default;
public:
    static Computer& getInstance();
    void storeVariable(const std::string& name, const Literal& l);
    void forgetVariable(const std::string& name);
    void pushVariable(const std::string& name);
    std::string evalLine(const std::string& s);
};

#endif

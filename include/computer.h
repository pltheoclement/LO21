#ifndef COMPUTER_H
#define COMPUTER_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "literal.h"

class Stack{
    std::vector<std::shared_ptr<Literal>> storage;
    Stack() = default;
public:
    static Stack& getInstance();
    std::vector<std::shared_ptr<Literal>>::const_reverse_iterator iterator() const;
    std::vector<std::shared_ptr<Literal>>::const_reverse_iterator end() const;
    void push(const std::shared_ptr<Literal>& pl);
    void pop();
    const std::shared_ptr<Literal>& top() const;
    size_t size() const;
};

class Computer{
    std::map<std::string, std::string> variables;
    std::string message;
    Computer() = default;
public:
    static Computer& getInstance();
    std::string getMessage() const;
    void storeVariable(const std::string& name, const Literal& l);
    void forgetVariable(const std::string& name);
    void pushVariable(const std::string& name);
    std::string evalLine(const std::string& s);
};

#endif

#include "computer.h"

void Stack::push(const std::shared_ptr<Literal>& pl) {
    storage.push_back(pl);
}

void Stack::pop() {
    storage.pop_back();
}

const std::shared_ptr<Literal> &Stack::top() const{
    return storage.back();
}

size_t Stack::size() const{
    return storage.size();
}

Computer *Computer::instance = nullptr;

Computer &Computer::getInstance() {
    if (instance == nullptr){
        instance = new Computer;
    }
    return *instance;
}

void Computer::storeVariable(const std::string &name, const Literal &l) {
    variables.at(name) = l.toString();
}

void Computer::forgetVariable(const std::string &name) {
    if (variables.contains(name)) {
        variables.erase(name);
    } else {
        message = "There is no variable with name " + name;
    }
}

void Computer::pushVariable(const std::string &name) {
    if (variables.contains(name)) {
        LiteralType lt = Literal::isLiteral(variables.at(name));
        switch (lt) {
            case lerror: message = "The variable " + name + " is invalid"; break;
            case lprogram: evalLine(variables.at(name)); break;
            default: stack.push(Literal::makeLiteral(variables.at(name), lt));
        }
    } else {
        message = "There is no variable with name " + name;
    }
}

void Computer::evalLine(const std::string &s) {
    // TODO
}


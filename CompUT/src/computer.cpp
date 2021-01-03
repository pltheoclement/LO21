#include "../include/operator.h"
#include "../include/computer.h"
#include <QDebug>
Stack &Stack::getInstance() {
    static Stack instance;
    return instance;
}

std::vector<std::shared_ptr<Literal>>::const_reverse_iterator Stack::iterator() const{
    return storage.crbegin();
}

std::vector<std::shared_ptr<Literal>>::const_reverse_iterator Stack::end() const {
    return storage.crend();
}

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

Computer &Computer::getInstance() {
    static Computer instance;
    return instance;
}

std::string Computer::getMessage() const {
    return message;
}

void Computer::storeVariable(const std::string &name, const Literal &l) {
    variables[name] = l.toString();
}

void Computer::forgetVariable(const std::string &name) {
    if (variables.count(name)) {
        variables.erase(name);
    } else {
        message = "There is no variable with name " + name;
    }
}

void Computer::pushVariable(const std::string &name) {
            qDebug() << "QString::fromStdString(variables.at(name))";
    if (variables.count(name)) {
        LiteralType lt = Literal::isLiteral(variables.at(name));
        qDebug() << "QString::fromStdString(variables.at(name))";
        qDebug() << QString::fromStdString(variables.at(name));
        switch (lt) {
            case lerror:
            case other : message = "The variable " + name + " is invalid"; break;
            case lprogram: evalLine(variables.at(name)); break;
            default: Stack::getInstance().push(Literal::makeLiteral(variables.at(name), lt));
        }
    } else {
        message = "There is no variable with name " + name;
    }
}

std::string Computer::getVariable(const std::string &name) {
    if (variables.count(name)) {
        return variables.at(name);
    } else {
        message = "There is no variable with name " + name;
        return "";
    }
}

std::string Computer::evalLine(const std::string &s) {
    message = "";
    // Checking program integrity
    int brackets = 0;
    for (char c : s){
        if (c == '[') brackets++;
        if (c == ']') brackets--;
        if (brackets < 0) {
            message = "Wrong bracket order";
            return s;
        }
    }
    if (brackets > 0) {
        message = "Too many opening brackets";
        return s;
    }
    if (brackets < 0) {
        message = "Too many closing brackets";
        return s;
    }

    // String processing
    std::string inst;
    std::string line = s + ' ';
    for (char c : s + " ") {
        if (c == ' ' && brackets == 0) {
            if (!inst.empty()) {
                if (Operator::isOperator(inst)) {
                    try {
                        Operator::getOperator(inst).apply(Stack::getInstance());
                    }
                    catch (OperatorException& e) {
                        message = e.getInfo();
                        return line;
                    }

                } else {
                    LiteralType lt = Literal::isLiteral(inst);
                    if (lt == lerror) {
                        message = "No such operator or literal " + inst;
                        return line;
                    } else if (lt == latom) {
                        if (variables.count(inst)) {
                            evalLine(variables.at(inst));
                        } else {
                            message = "No variable or program called " + inst;
                            return line;
                        }
                    } else {
                        try {
                            Stack::getInstance().push(Literal::makeLiteral(inst, lt));
                        }
                        catch (LiteralException& e) {
                            message = e.getInfo();
                            return line;
                        }

                    }
                }
            }
            line = line.substr(inst.length(), line.length()-1);
            inst = "";
        } else {
            if (c == '[') {
                brackets++;
            } else if (c == ']') {
                brackets--;
            }
            inst += c;
        }
    }
    return "";
}


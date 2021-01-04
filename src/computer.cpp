#include <fstream>

#include "../include/computer.h"
#include "../include/operator.h"

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
    if (variables.count(name)) {
        LiteralType lt = Literal::isLiteral(variables.at(name));
        switch (lt) {
            case lerror: message = "The variable " + name + " is invalid"; break;
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

void Computer::saveToFile(const std::string &filename) const {
    std::fstream file;
    file.open(filename, std::ios::out);
    for (auto& entry : variables) {
        file << entry.first << ';' << entry.second << std::endl;
    }
    file.close();
}

void Computer::loadFromFile(const std::string &filename) {
    std::fstream file;
    file.open(filename, std::ios::in);
    std::string line;
    int lc = 0;
    while (std::getline(file, line)) {
        std::string name, value;
        if (line.size() < 3) {
            message = "Invalid file " + filename + " (error line " + std::to_string(lc) + ")";
            file.close();
            return;
        }
        unsigned int i = 0;
        while (line[i] != ';') name += line[i++];
        i++;
        while (i < line.size()) value += line[i++];
        LiteralType lt = Literal::isLiteral(value);
        if (Literal::isLiteral(name) != latom || lt == lerror) {
            message = "Invalid file " + filename + " (error line " + std::to_string(lc) + ")";
            file.close();
            return;
        }
        storeVariable(name, *Literal::makeLiteral(value, lt));
        lc++;
    }
    file.close();
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
                        message = "Invalid literal or operator: " + inst;
                        return line;
                    } else if (lt == latom) {
                        if (variables.count(inst)) {
                            std::string val = variables.at(inst);
                            evalLine(val[0] == '[' ? val.substr(1, val.size()-2) : val);
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


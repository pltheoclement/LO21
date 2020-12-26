#ifndef HEADERS_LITERAL_H_
#define HEADERS_LITERAL_H_
#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum LiteralType {linteger,lrational,lreal,latom,lexpression,lprogram,lerror, other};

class LiteralException {
    std::string info;
public:
    LiteralException(const std::string& s): info(s){};
    std::string getInfo(){ return info;}
};

class Literal {

    LiteralType type;
public:

    static LiteralType isLiteral(const std::string& s);
    static const std::shared_ptr<Literal> makeLiteral(const std::string& s, LiteralType t);

    LiteralType getType(){ return type;}
    virtual std::string toString() const = 0;
    virtual std::shared_ptr<Literal> getCopy() const { return makeLiteral(this->toString(), this->type);}
    virtual ~Literal() {}
};

class LInteger : public Literal {

    LiteralType type = linteger;
    int value;
public:
    LInteger(const int& i): value(i){}
    int getValue() const { return value;}
    const std::shared_ptr<LInteger> operator=(const std::shared_ptr<LInteger>){
        return std::make_shared<LInteger>(this->value);
    }
    static const std::shared_ptr<LInteger> makeLiteral(const int& i);
    std::string toString() const { return std::to_string(value);}
    ~LInteger(){}
};

class LReal : public Literal {

    LiteralType type = lreal;
    double value;
public:
    LReal(const double& d): value(d){}
    LReal(const LInteger& i): value(double(i.getValue())){}
    double getValue() const { return value;}
    static const std::shared_ptr<LReal> makeLiteral(const double& d);
    std::string toString() const{ return std::to_string(value);}
    ~LReal(){}
};

class LRational : public Literal {

    LiteralType type = lrational;
    int num;
    int den;
    void simplify();
public:
    LRational(const int& n, const int& d): num(n),den(d){ this->simplify();}
    LRational(const LInteger& i): num(i.getValue()), den(1){}
    int getNum() const { return num;}
    int getDen() const { return den;}
    static std::shared_ptr<LRational> makeLiteral(const int& n, const int& d);
    std::string toString() const { return std::to_string(num)+'/'+std::to_string(den);}
    LInteger toLInteger(){ LInteger i(int(num/den)); return i;}
    LReal toLReal(){ LReal r(double(num/den)); return r;}
    ~LRational(){}
};

class LAtom : public Literal {

    LiteralType type = latom;
    std::string value;
public:
    std::string getValue() const { return value;}
    std::string toString() const {return value;}
    ~LAtom(){}
};

class LExpression : public LAtom {

    LiteralType type = lexpression;
    std::string value;
public:
    std::string getValue() const { return value;}
    std::string toString() const { return '\''+value+'\'';}
    ~LExpression(){}
};

class LProgram : public Literal {
    std::string program;
    LiteralType type = lprogram;
public:
    //std::vector<Literal> getLiterals() const;
    //LiteralIterator iter(){ return LiteralIterator(*this);}
    std::string toString() const;
    ~LProgram(){}
};

/* class LiteralIterator{

    size_t pos;
public:
    LiteralIterator(Stack s);
    LiteralIterator(LProgram p);
    void next();
    Literal item();
    bool isDone();
}; */

#endif

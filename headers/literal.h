#ifndef HEADERS_LITERAL_H_
#define HEADERS_LITERAL_H_
#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum LiteralType {linteger,lrational,lreal,latom,lexpression,lprogram,other};

class Literal {

    LiteralType type;
public:

    static LiteralType isLiteral(const std::string& s);
    static Literal* makeLiteral(const std::string& s, LiteralType t);

    LiteralType getType(){ return type;}
    virtual std::string toString() = 0;
    virtual ~Literal() {}
};

class LInteger : public Literal {

    LiteralType type = linteger;
    int value;
public:
    LInteger(const int& i): value(i){}
    //LInteger(const LReal& r): value(int(r.getValue())){}
    //LInteger(const LRational& f): value(int(f.getNum()/f.getDen())){}
    int getValue() const { return value;}
    static LInteger* makeLiteral(const int& i);
    std::string toString(){ return std::to_string(value);}
    ~LInteger(){}
};

class LReal : public Literal {

    LiteralType type = lreal;
    double value;
public:
    LReal(const double& d): value(d){}
    LReal(const LInteger& i): value(double(i.getValue())){}
    //LReal(const LRational& f): value(f.getNum()/f.getDen()){}
    double getValue() const { return value;}
    static LReal* makeLiteral(const double& d);
    std::string toString(){ return std::to_string(value);}
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
    static LRational* makeLiteral(const int& n, const int& d);
    std::string toString(){ return std::to_string(num)+'/'+std::to_string(den);}
    ~LRational(){}
};

class LAtom : public Literal {

    LiteralType type = latom;
    std::string value;
public:
    std::string getValue() const { return value;}
    ~LAtom(){}
};

class LExpression : public LAtom {

    LiteralType type = lexpression;
    std::string value;
public:
    std::string getValue() const { return value;}
    std::string toString(){ return '\''+value+'\'';}
    ~LExpression(){}
};

class LProgram : public Literal {

    LiteralType type = lprogram;
public:
    std::vector<Literal> getLiterals() const;
    //LiteralIterator iter(){ return LiteralIterator(*this);}
    std::string toString();
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

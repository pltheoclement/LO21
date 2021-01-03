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
public:
    static LiteralType isLiteral(const std::string& s);
    static const std::shared_ptr<Literal> makeLiteral(const std::string& s, LiteralType t);

    virtual LiteralType getType() = 0;
    virtual std::string toString() const = 0;
    virtual std::shared_ptr<Literal> getCopy() { return makeLiteral(this->toString(), this->getType());}
    virtual ~Literal() {}
};

class LInteger : public Literal {

    int value;
public:
    LiteralType getType(){ return linteger;}
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

    double value;
public:
    LiteralType getType(){ return lreal;}
    LReal(const double& d): value(d){}
    LReal(const LInteger& i): value(double(i.getValue())){}
    double getValue() const { return value;}
    static const std::shared_ptr<LReal> makeLiteral(const double& d);
    std::string toString() const{ return std::to_string(value);}
    ~LReal(){}
};

class LRational : public Literal {

    int num;
    int den;
    void simplify();
public:
    LiteralType getType(){ return lrational;}
    LRational(const int& n, const int& d): num(n),den(d){if (den == 0) throw LiteralException("Null denominator"); this->simplify();}
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

    std::string value;
public:
    LiteralType getType(){ return latom;}
    std::string getValue() const { return value;}
    std::string toString() const {return value;}
    ~LAtom(){}
};

class LExpression : public LAtom {

    std::string value;
public:
    LiteralType getType(){ return lexpression;}
    std::string getValue() const { return value;}
    std::string toString() const { return '\''+value+'\'';}
    static const std::shared_ptr<LExpression>makeLiteral(std::string s);
    LExpression(std::string s) : value(s){}
    ~LExpression(){}
};

class LProgram : public Literal {
    std::string program;
public:
    LiteralType getType(){ return lprogram;}
    std::string toString() const;
    static const std::shared_ptr<LProgram>makeLiteral(std::string s);
    LProgram(std::string s) : program(s){}
    std::string getValue() {return program;}
    ~LProgram(){}
};

#endif

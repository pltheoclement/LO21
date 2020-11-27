#include <iostream>
#include <string>
#include <vector>

enum LiteralType {linteger,lrational,lreal,latom,lexpression,lprogram,oper};

class Literal {

    LiteralType type;
public:

    static LiteralType isLiteral(const std::string& s);
    static Literal makeLiteral(const std::string& s, LiteralType t);

    LiteralType getType(){ return type;};
    std::string toString();
};

class LInteger : public Literal {

    LiteralType type = linteger;
    int value;
public:
    int getValue() const { return value;};
    static LInteger makeLiteral(const int& i);
};

class LReal : public Literal {

    LiteralType type = lreal;
    double value;
public:
    double getValue() const { return value;};
    static LReal makeLiteral(const double& d);
};

class LAtom : public Literal {

    LiteralType type = latom;
    std::string value;
public:
    std::string getValue() const { return value;}
};

class LExpression : public LAtom {

    LiteralType type = lexpression;
    std::string value;
public:
    std::string getValue() const { return value;}
};

class LProgram : public Literal {

    LiteralType type = lprogram;
public:
    std::vector<Literal> getLiterals() const;
    //LiteralIterator iter();
};

class LRational : public Literal {

    LiteralType type = lrational;
    int num;
    int den;
    void simplify();
public:
    int getNum() const { return num;}
    int getDen() const { return den;}
    static LRational makeLiteral(const int& n, const int& d);
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

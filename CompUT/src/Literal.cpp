#include <string>
#include <vector>
#include <memory>
#include <set>

#include "../include/literal.h"

LiteralType Literal::isLiteral(const std::string& s){
    if (s[0] >= '0' && s[0] <= '9'){
        unsigned int nslash = 0, ndot = 0;
        for(char c : s){
            if (c=='/')
                nslash++;
            else if (c=='.')
                ndot++;
            else if (c < '0' || c > '9')
                return lerror;
        }
        if (nslash == 0 && ndot == 0)
            return linteger;
        else if (nslash == 1 && ndot == 0)
            return lrational;
        else if (nslash == 0 && ndot == 1)
            return lerror;
    } else {
        if (s[0] >= 'A' && s[0] <= 'Z') {
            for (char c : s)
                if ((c < '0' || c > '9') && (c < 'A' || c > 'Z'))
                    return lerror;
            return latom;
        }
        if (s[0] == '.' && s.size() >= 2) {
            for (char c : s.substr(1, s.size()-1))
                if (c < '0' || c > '9')
                    return lerror;
            return lreal;
        }
        if(s[0]=='"' && s[s.size()-1] == '"' && s.size() >= 3) {
            if (s[1] >= 'A' && s[1] <= 'Z') {
                for (char c : s.substr(1, s.size()-2))
                    if ((c < '0' || c > '9') && (c < 'A' || c > 'Z'))
                        return lerror;
                return lexpression;
            }
        }
        if(s[0]=='[' && s[s.size()-1] == ']') {
            static std::set<char> allowedChars;
            if (allowedChars.empty()) {
                std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 []\".+-*/";
                allowedChars.insert(chars.begin(), chars.end());
            }
            for (char c : s) {
                if (allowedChars.count(c) == 0)
                    return lerror;
            }
            return lprogram;
        }
    }
    return lerror;
}

const std::shared_ptr<Literal> Literal::makeLiteral(const std::string& s, LiteralType t){
    switch(t){
        case linteger : return LInteger::makeLiteral(std::stoi(s));
        case lreal : return LReal::makeLiteral(std::stod(s));
        case lrational : {
                std::string n;
                std::string d;
                unsigned int i=0;
                while(s[i]!='/'){n += s[i]; i++;}
                for(i++; i<s.size(); i++) d += s[i];
                return LRational::makeLiteral(std::stoi(n),std::stoi(d));
            }
        case lprogram : return LProgram::makeLiteral(s);
        case lexpression: return LExpression::makeLiteral(s.substr(1, s.size() - 2));

        default : throw LiteralException("Invalid Literal");
    }
}

const std::shared_ptr<LInteger> LInteger::makeLiteral(const int& i){
    return std::make_shared<LInteger>(i);
}

const std::shared_ptr<LReal> LReal::makeLiteral(const double& d){
    return std::make_shared<LReal>(d);
}

std::shared_ptr<LRational> LRational::makeLiteral(const int& n, const int& d){
    return std::make_shared<LRational>(n,d);
}

std::string LProgram::toString() const {
    return program;
}

const std::shared_ptr<LProgram> LProgram::makeLiteral(std::string s){
    return std::make_shared<LProgram>(s);
}

const std::shared_ptr<LExpression> LExpression::makeLiteral(std::string s){
    return std::make_shared<LExpression>(s);
}

void LRational::simplify(){
    if(num == 0) { den = 1; return;}
    if(den == 0) { return; }
    int a = num, b = den;
    if(a<0) a = -a;
    if(b<0) b = -b;
    while (a!=b) {if(a>b) a=a-b; if(b>a) b=b-a;}
    num /= a;
    den /= b;
    if(den<0) {den=-den; num=-num;}
}

#include "Literal.h"

LiteralType Literal::isLiteral(const std::string& s){
    if (s[0] >= 48 && s[0] <= 57){
        for(unsigned int i=1; i<s.size(); i++){
            if(s[i]=='/') return lrational;
            if(s[i]=='.') return lreal;
        }
        return linteger;
    }
    else{
        if(s[0]=='[') return lprogram;
        if(s[0]==39) return lexpression;
        /*for(unsigned int i=0; i<nbvar; i++)
            if(!(strcmp(getvariable(i)[0], s))) return latom;*/
        return oper;
    }
}

Literal Literal::makeLiteral(const std::string& s, LiteralType t){
    if(t == linteger) return makeLiteral(std::stoi(s));
}

LInteger LInteger::makeLiteral(const int& i){
    LInteger* it = new LInteger;
    it->value = i;
    return *it;
}

LReal LReal::makeLiteral(const double& d){
    LReal* re = new LReal;
    re->value = d;
    return *re;
}

LRational LRational::makeLiteral(const int& n, const int& d){
    LRational* ra = new LRational;
    ra->num = n;
    ra->den = d;
    ra->simplify();
    return *ra;
}

std::string Literal::toString(){
   // if(type==linteger) return std::to_string()
}

/* std::vector<Literal> LProgram::getLiterals() const {
}

LiteralIterator LProgram::iter(){
} */

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

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
        return other;
    }
}

std::shared_ptr<Literal> Literal::makeLiteral(const std::string& s, LiteralType t){
    switch(t){
        case linteger : return LInteger::makeLiteral(std::stoi(s));
        case lreal : return LReal::makeLiteral(std::stod(s));
        case lrational :
            {
            std::string n="";
            std::string d="";
            unsigned int i=0;
            while(s[i]!='/'){n += s[i]; i++;}
            for(; i<s.size(); i++) d += s[i];
            return LRational::makeLiteral(std::stod(n),std::stod(d));
            }
        default : throw "Erreur : impossible de construire le literal !";
    }
}

std::shared_ptr<LInteger> LInteger::makeLiteral(const int& i){
    auto it = std::make_shared<LInteger>(i);
    return it;
}

std::shared_ptr<LReal> LReal::makeLiteral(const double& d){
    auto re = std::make_shared<LReal>(d);
    return re;
}

std::shared_ptr<LRational> LRational::makeLiteral(const int& n, const int& d){
    auto ra = std::make_shared<LRational>(n,d);
    return ra;
}

std::vector<Literal> LProgram::getLiterals() const {

}
std::string LProgram::toString(){
    std::string s = "[";
    for(size_t i=0; i<this->getLiterals().size(); i++) s += " " + this->getLiterals()[i].toString() ;
    s += " ]";
    return s;
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

#include "element.h"


IntElement::IntElement(){
    val = 0;
}
IntElement::IntElement(int v){
    val = v;
}
int IntElement::getVal() const{
    return val;
}
void IntElement::setVal(int v){
    val = v;
}
IntElement& IntElement::operator+=(const IntElement& i){
    val += i.val;
    return (*this);
}
IntElement& IntElement::operator-=(const IntElement& i){
    val -= i.val;
    return (*this);
}
IntElement& IntElement::operator*=(const IntElement& i){
    val *= i.val;
    return (*this);
}
bool IntElement::operator==(const IntElement& i) const{
    if(val == i.val){return true;}
    else{return false;}
}
IntElement IntElement::operator+(const IntElement& i){
    int tempVal = val + i.val;
    IntElement ielem(tempVal);
    return ielem;
}
IntElement IntElement::operator-(const IntElement& i){
    int tempVal = val - i.val;
    IntElement ielem(tempVal);
    return ielem;
}
IntElement IntElement::operator*(const IntElement& i){
    int tempVal = val * i.val;
    IntElement ielem(tempVal);
    return ielem;
}
std::string IntElement::toString() const{
    return std::to_string(val);
}
Element* IntElement::clone() const{
    IntElement *pElem = new IntElement(val);
    return pElem;
}
int IntElement::evaluate(const Valuation& valu) const{
    return val;
}





std::ostream& operator<<(std::ostream& os, IntElement& m){
    os << m.toString();
    return os;
}
std::ostream& operator<<(std::ostream& os, VariableElement& m){
    os << m.toString();
    return os;
}






VariableElement::VariableElement(){
    var = 'g';
}
VariableElement::VariableElement(char v){
    var = v;
}
char VariableElement::getVal() const{
    return var;
}
void VariableElement::setVal(int v){
    var = v;
}
Element* VariableElement::clone() const{
    VariableElement *pElem = new VariableElement(var);
    return pElem;
}
std::string VariableElement::toString() const{
    std::string temp = "";
    return temp + var;
}
int VariableElement::evaluate(const Valuation& valu) const{
    auto it = valu.find(var);
    if (it == valu.end())
        throw(std::invalid_argument("Var value not in Valuation valu."));
    return (*it).second;
}
bool VariableElement::operator==(const VariableElement& i) const{
    return var == i.getVal();
}


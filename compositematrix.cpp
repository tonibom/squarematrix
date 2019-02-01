#include "compositematrix.h"

CompositeSquareMatrix::CompositeSquareMatrix(const SquareMatrix& op1, const SquareMatrix& op2,
                          const std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)> opr,
                          char ops)
{
    oprnd1 = uniq_sqm_ptr(op1.clone());
    oprnd2 = uniq_sqm_ptr(op2.clone());
    oprtor = opr;
    op_sym = ops;
}

CompositeSquareMatrix::CompositeSquareMatrix(const CompositeSquareMatrix& m){
    oprnd1 = uniq_sqm_ptr(m.oprnd1->clone());
    oprnd2 = uniq_sqm_ptr(m.oprnd2->clone());
    oprtor = m.oprtor;
    op_sym = m.op_sym;
}

CompositeSquareMatrix::CompositeSquareMatrix(CompositeSquareMatrix&& m){
    std::swap(oprnd1, m.oprnd1);
    std::swap(oprnd2, m.oprnd2);
    std::swap(oprtor, m.oprtor);
    std::swap(op_sym, m.op_sym);
}

CompositeSquareMatrix& CompositeSquareMatrix::operator=(const CompositeSquareMatrix& m){
    oprnd1 = uniq_sqm_ptr(m.oprnd1->clone());
    oprnd2 = uniq_sqm_ptr(m.oprnd2->clone());
    oprtor = m.oprtor;
    op_sym = m.op_sym;
    return *this;
}

CompositeSquareMatrix& CompositeSquareMatrix::operator=(CompositeSquareMatrix&& m){
    oprnd1 = std::move(m.oprnd1);
    oprnd2 = std::move(m.oprnd2);
    oprtor = std::move(m.oprtor);
    op_sym = std::move(m.op_sym);
    return *this;
}

SquareMatrix* CompositeSquareMatrix::clone() const{
    CompositeSquareMatrix *pSqm = new CompositeSquareMatrix(*this);
    return pSqm;
}

void CompositeSquareMatrix::print(std::ostream& os) const{
    os << toString() << std::endl;
}

std::string CompositeSquareMatrix::toString() const{
    std::stringstream ss;
    ss << "(" << oprnd1->toString() << op_sym << oprnd2->toString() << ")";
    return ss.str();
}

ConcreteSquareMatrix CompositeSquareMatrix::evaluate(const Valuation& valu) const{
    ConcreteSquareMatrix temp;

    ConcreteSquareMatrix temp1 = oprnd1->evaluate(valu);
    ConcreteSquareMatrix temp2 = oprnd2->evaluate(valu);
    temp = oprtor(temp1, temp2);

    return temp;
}

std::ostream& operator<<(std::ostream& os, CompositeSquareMatrix& m)
{
    os << m.toString();
    return os;
}

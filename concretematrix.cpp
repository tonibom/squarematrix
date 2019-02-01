#include "concretematrix.h"


ConcreteSquareMatrix::ConcreteSquareMatrix(){
    n = 0;
}

ConcreteSquareMatrix::ConcreteSquareMatrix(const std::string& str){

    std::stringstream inputstream(str);
    char c;
    int number;
    unsigned int row_num = 0;
	n = std::numeric_limits<int>::max();
	unsigned int numbers_in_row = 0;
	bool nFound = false;

	inputstream >> c;
	if (!inputstream.good() || c != '[')
		throw(std::invalid_argument("Invalid init string"));

	while (row_num < n){
        std::vector<uniq_intelem_ptr> row;
		inputstream >> c;
		if (!inputstream.good() || c != '[')
			throw(std::invalid_argument("Invalid init string"));

		while(c != ']'){

			inputstream >> number;
			if (!inputstream.good())
				throw(std::invalid_argument("Invalid init string"));

			inputstream >> c;
			if (!inputstream.good() || (c != ',' && c != ']'))
				throw(std::invalid_argument("Invalid init string"));

            numbers_in_row++;
            row.push_back(uniq_intelem_ptr(new IntElement(number)));
		}

		if(!nFound)
			n = numbers_in_row;
			nFound = true;

		if (nFound && numbers_in_row != n)
			throw(std::invalid_argument("Invalid init string"));
		row_num++;
		numbers_in_row = 0;
		elements.push_back(std::move(row));
	}

	inputstream >> c;
	if (c != ']' || !inputstream.good())
		throw(std::invalid_argument("Invalid init string"));

	inputstream >> c;
	if (inputstream.good())
		throw(std::invalid_argument("Invalid init string"));
}

ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix& m){

    for(auto& m_row : m.elements){
        std::vector<uniq_intelem_ptr> vect;

        for(auto& m_ielem : m_row){
            vect.push_back(uniq_intelem_ptr(static_cast<IntElement*>(m_ielem->clone())));
        }

        elements.push_back(std::move(vect));
    }
    n = m.n;
}
ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix&& m) : n(m.n), elements(std::move(m.elements)){
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(const ConcreteSquareMatrix& m){

    if(this == &m){return *this;}

    ConcreteSquareMatrix temp(m);
    elements.clear();
    elements = std::move(temp.elements);
    n = m.n;

    return *this;
}
ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(ConcreteSquareMatrix&& m){
    n = m.n;
    std::swap(elements, m.elements);
    return *this;
}

ConcreteSquareMatrix ConcreteSquareMatrix::transpose() const{
    ConcreteSquareMatrix temp;
    temp.n = n;

    temp.elements = std::vector<std::vector<uniq_intelem_ptr>>(n);
    for(auto& row : elements){

        int i = 0;

        for(auto& ielem : row){
            temp.elements[i].push_back(uniq_intelem_ptr(static_cast<IntElement*>(ielem->clone())));
            i++;
        }
    }
    return temp;
}

ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& m){
    if(n != m.n){
        throw(std::invalid_argument("Invalid init matrixes"));
    }

    auto row_it = m.elements.begin();

    for(auto& row : elements)
    {
        auto a_it = row_it->begin();
        for(auto& a : row)
        {
            *a += **a_it++;
        }
        row_it++;
    }

    return *this;
}
ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix& m){
    if(n != m.n){
        throw(std::invalid_argument("Invalid init matrixes"));
    }

    auto row_it = m.elements.begin();

    for(auto& row : elements)
    {
        auto a_it = row_it->begin();
        for(auto& a : row)
        {
            *a -= **a_it++;
        }
        row_it++;
    }

    return *this;
}
ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix& m){

    ConcreteSquareMatrix temp(*this);

    if(n != m.n){
        throw(std::invalid_argument("Invalid init matrixes"));
    }

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            *elements[i][j] = 0;
            for (unsigned int k = 0; k < n; k++) {
                *elements[i][j] += (*temp.elements[i][k] * *m.elements[k][j]);
            }
        }
    }

    return *this;
}
bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix& m) const{

    ConcreteSquareMatrix temp(m);
    ConcreteSquareMatrix temp2(*this);

    if(temp2.toString() == temp.toString()){return true;}
    else{return false;}
}


void ConcreteSquareMatrix::print(std::ostream& os) const{
    os << toString() << std::endl;
}

std::string ConcreteSquareMatrix::toString() const{
    std::stringstream ss;
    ss << "[";
    for(auto& row : elements){
        ss << "[";
        bool first = true;

        for(auto& ielem : row){

            if(!first){
                ss << ",";
            }

            ss << *ielem;
            first = false;
        }
        ss << "]";
    }
    ss << "]";
    return ss.str();
}

ConcreteSquareMatrix ConcreteSquareMatrix::evaluate(const Valuation& valu) const{
    return *this;
}

SquareMatrix* ConcreteSquareMatrix::clone() const{
    ConcreteSquareMatrix *pSqm = new ConcreteSquareMatrix(*this);
    return pSqm;
}

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
    ConcreteSquareMatrix temp(m1);
    temp += m2;
    return temp;
}
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
    ConcreteSquareMatrix temp(m1);
    temp -= m2;
    return temp;
}
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
    ConcreteSquareMatrix temp(m1);
    temp *= m2;
    return temp;
}

std::ostream& operator<<(std::ostream& os, ConcreteSquareMatrix& m)
{
    os << m.toString();
    return os;
}

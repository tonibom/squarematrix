#include "symbolicmatrix.h"

SymbolicSquareMatrix::SymbolicSquareMatrix(){
    n = 0;
}
SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string& str){

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
        std::vector<uniq_elem_ptr> row;
		inputstream >> c;
		if (!inputstream.good() || c != '[')
			throw(std::invalid_argument("Invalid init string"));

		while(c != ']'){

			inputstream >> number;
			if (!inputstream.good()){
			    inputstream.clear();
                inputstream >> c;
                if (!inputstream.good() or !isalpha(c)){
                    throw(std::invalid_argument("Invalid init string"));
                }
                else{
                    row.push_back(uniq_elem_ptr(new VariableElement(c)));
                }
			}
            else{
                row.push_back(uniq_intelem_ptr(new IntElement(number)));
            }
			inputstream >> c;
			if (!inputstream.good() || (c != ',' && c != ']'))
				throw(std::invalid_argument("Invalid init string"));

            numbers_in_row++;
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
SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& m){
    for(auto& m_row : m.elements){
        std::vector<uniq_elem_ptr> vect;

        for(auto& m_ielem : m_row){
            vect.push_back(uniq_elem_ptr(static_cast<IntElement*>(m_ielem->clone())));
        }

        elements.push_back(std::move(vect));
    }
    n = m.n;
}
SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& m): n(m.n), elements(std::move(m.elements)){
}
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix& m){

    if(this == &m){return *this;}

    SymbolicSquareMatrix temp(m);
    elements.clear();
    elements = std::move(temp.elements);
    n = m.n;

    return *this;
}
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix&& m){
    n = m.n;
    std::swap(elements, m.elements);
    return *this;
}
SymbolicSquareMatrix SymbolicSquareMatrix::transpose() const{
    SymbolicSquareMatrix temp;
    temp.n = n;

    temp.elements = std::vector<std::vector<uniq_elem_ptr>>(n);
    for(auto& row : elements){

        int i = 0;

        for(auto& ielem : row){
            temp.elements[i].push_back(uniq_elem_ptr(static_cast<IntElement*>(ielem->clone())));
            i++;
        }
    }
    return temp;
}
bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& m) const{

    SymbolicSquareMatrix temp(m);
    SymbolicSquareMatrix temp2(*this);

    if(temp2.toString() == temp.toString()){return true;}
    else{return false;}
}
void SymbolicSquareMatrix::print(std::ostream& os) const{
    SymbolicSquareMatrix temp(*this);
    os << temp.toString() << std::endl;
}
std::string SymbolicSquareMatrix::toString() const{
    std::stringstream ss;
    ss << "[";
    for(auto& row : elements){
        ss << "[";
        bool first = true;

        for(auto& elem : row){

            if(!first){
                ss << ",";
            }
            std::string temp = "";
            temp += elem->toString();
            if(temp.length() <= 1){
                VariableElement velem(temp[0]);
                ss << velem;
            }
            else{
                IntElement ielem(std::stoi(temp));
                ss << ielem;
            }
            first = false;
        }
        ss << "]";
    }
    ss << "]";
    return ss.str();
}
ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& valu) const{

    std::string matrix = "[";

    for(auto& row : elements){

        matrix += "[";
        bool first = true;

        for(auto& elem : row){

            if(!first){
                matrix += ",";
            }
            matrix += std::to_string(elem->evaluate(valu));
            first = false;
        }
        matrix += "]";
    }
    matrix += "]";
    ConcreteSquareMatrix temp3(matrix);
    return temp3;
}

SquareMatrix* SymbolicSquareMatrix::clone() const{
    SymbolicSquareMatrix *pSqm = new SymbolicSquareMatrix(*this);
    return pSqm;
}

std::ostream& operator<<(std::ostream& os, SymbolicSquareMatrix& m)
{
    os << m.toString();
    return os;
}

/** \file symbolicmatrix.h
*/

#ifndef SYMBOLICMATRIX_H_INCLUDED
#define SYMBOLICMATRIX_H_INCLUDED

#include "squarematrix.h"
#include "concretematrix.h"
#include "element.h"
#include "catch.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>
#include <numeric>
#include <algorithm>


/** \class SymbolicSquareMatrix
* \brief This is a class for storing and handling squarematrixes with integer and character values.
*/
class SymbolicSquareMatrix : public SquareMatrix {

private:

    /** \brief The dimension length of the squarematrix
    */
    unsigned int n;

    /** \brief Two dimensional vector to hold the pointers to the Elements
    */
    std::vector< std::vector<uniq_elem_ptr> > elements;

public:

    /** \brief Constructor without parameters
    * This will construct a SymbolicSquareMatrix with the size of 0.
    */
    SymbolicSquareMatrix();

    /** \brief Constructor which constructs a SymbolicSquareMatrix with std::string as a specification
    * \throw std::invalid_argument("Invalid init string") - if the parameter string wasn't a valid squarematrix
    * \param std::string& str - string according to which the SymbolicSquareMatrix will be constructed
    */
    SymbolicSquareMatrix(const std::string& str);

    /** \brief Constructor which duplicates another SymbolicSquareMatrix
    * \param SymbolicSquareMatrix& m - SymbolicSquareMatrix which is to be duplicated
    */
    SymbolicSquareMatrix(const SymbolicSquareMatrix& m);

    /** \brief Move constructor which steals another SymbolicSquareMatrix's values
    * \param SymbolicSquareMatrix&& m - temporary SymbolicSquareMatrix from which values are to be stolen
    */
    SymbolicSquareMatrix(SymbolicSquareMatrix&& m);

    /** \brief Default destructor
    */
    virtual ~SymbolicSquareMatrix() = default;

    /** \brief = operator for assigning a SymbolicSquareMatrix over another SymbolicSquareMatrix
    * \param SymbolicSquareMatrix& m - The SymbolicSquareMatrix which is to be assigned
    * \return SymbolicSquareMatrix& - The resulting SymbolicSquareMatrix
    */
    SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix& m);

    /** \brief = operator for assigning a temporary SymbolicSquareMatrix's values over another SymbolicSquareMatrix's
    * \param SymbolicSquareMatrix&& m - Temporary SymbolicSquareMatrix which values are to be used in assignment
    * \return SymbolicSquareMatrix& - The resulting SymbolicSquareMatrix
    */
    SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&& m);

    /** \brief Function for cloning a SymbolicSquareMatrix
    * \return SquareMatrix *pMatrix - Pointer variable that points to a fresh copy of the SymbolicSquareMatrix
    */
    SquareMatrix* clone() const override;

    /** \brief Function for transposing a SymbolicSquareMatrix
    * \return SymbolicSquareMatrix temp - Transposed SymbolicSquareMatrix
    */
    SymbolicSquareMatrix transpose() const;

    /** \brief == operator for comparing two SymbolicSquareMatrixes
    * \param SymbolicSquareMatrix& m - The other SymbolicSquareMatrix
    * \return bool - true if SymbolicSquareMatrixes are equal, false if they're not
    */
    bool operator==(const SymbolicSquareMatrix& m) const;

    /** \brief Function for printing SymbolicSquareMatrix
    * \param std::ostream& os - Outputstream for the output
    * \return void - This function doesn't return anything.
    */
    void print(std::ostream& os) const override;

    /** \brief Function for displaying SymbolicSquareMatrix as a string in proper format
    * \return std::string ss - SymbolicSquareMatrix as a properly formatted string
    */
    std::string toString() const override;

    /** \brief Function for valuating the Elements of the SymbolicSquareMatrix
    * \param Valuation& valu - std::map<char, int> for storing values for the encapsulated variables
    * \throw std::invalid_argument("Var value not in Valuation valu.") - if encapsulated character in any of the Elements has no matching integer value in Valuation valu
    * \return ConcreteSquareMatrix - ConcreteSquareMatrix in which all of the SymbolicSquareMatrix's VariableElements's character values have been replaced by integer values according to Valuation valu
    */
    ConcreteSquareMatrix evaluate(const Valuation& valu) const override;
};

/** \brief << operator for outputting SymbolicSquareMatrix.
* \param std::ostream& os - Outputstream for the output
* \param SymbolicSquareMatrix& m - SymbolicSquareMatrix which to output
* \return std::ostream& os - The outputstream for the output with the SymbolicSquareMatrix inside
*/
std::ostream& operator<<(std::ostream& os, SymbolicSquareMatrix& m);

#endif // SYMBOLICMATRIX_H_INCLUDED



/** \file compositematrix.h
*/
#ifndef COMPOSITEMATRIX_H_INCLUDED
#define COMPOSITEMATRIX_H_INCLUDED

#include "squarematrix.h"
#include "concretematrix.h"
#include "valuation.h"
#include "catch.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>
#include <numeric>
#include <algorithm>
#include <functional>

/** \class CompositeSquareMatrix
* \brief This is a composite class for storing and handling squarematrixes with integer and character values.
*/
class CompositeSquareMatrix : public SquareMatrix{
private:

    /** The first SquareMatrix of the CompositeSquareMatrix
    */
    uniq_sqm_ptr oprnd1;

    /** The second SquareMatrix of the CompositeSquareMatrix
    */
    uniq_sqm_ptr oprnd2;

    /** The mathematical operator on CompositeSquareMatrix
    */
    std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)> oprtor;

    /** The operator symbol character
    */
    char op_sym;

public:

    /** \brief Constructor for CompositeSquareMatrix
    * \param const SquareMatrix& op1 - The first SquareMatrix of the CompositeSquareMatrix
    * \param const SquareMatrix& op2 - The second SquareMatrix of the CompositeSquareMatrix
    * \param const std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)> opr - The mathematical operator on CompositeSquareMatrix
    * \param char ops - The operator symbol character
    */
    CompositeSquareMatrix(const SquareMatrix& op1, const SquareMatrix& op2,
                          const std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&, const ConcreteSquareMatrix&)> opr,
                          char ops);

    /** \brief Constructor which duplicates another CompositeSquareMatrix
    * \param CompositeSquareMatrix& m - CompositeSquareMatrix which is to be duplicated
    */
    CompositeSquareMatrix(const CompositeSquareMatrix& m);

    /** \brief Move constructor which steals another CompositeSquareMatrix's values
    * \param CompositeSquareMatrix&& m - temporary CompositeSquareMatrix from which values are to be stolen
    */
    CompositeSquareMatrix(CompositeSquareMatrix&& m);

    /** \brief destructor
    */
    ~CompositeSquareMatrix() = default;

    /** \brief = operator for assigning a CompositeSquareMatrix over another CompositeSquareMatrix
    * \param CompositeSquareMatrix& m - The CompositeSquareMatrix which is to be assigned
    * \return CompositeSquareMatrix& - The resulting CompositeSquareMatrix
    */
    CompositeSquareMatrix& operator=(const CompositeSquareMatrix& m);

    /** \brief = operator for assigning a temporary CompositeSquareMatrix's values over another CompositeSquareMatrix's
    * \param CompositeSquareMatrix&& m - Temporary CompositeSquareMatrix which values are to be used in assignment
    * \return CompositeSquareMatrix& - The resulting CompositeSquareMatrix
    */
    CompositeSquareMatrix& operator=(CompositeSquareMatrix&& m);

    /** \brief Function for cloning a CompositeSquareMatrix
    * \return SquareMatrix *pMatrix - Pointer variable that points to a fresh copy of the CompositeSquareMatrix
    */
    SquareMatrix* clone() const override;

    /** \brief Function for printing CompositeSquareMatrix
    * \param std::ostream& os - Outputstream for the output
    * \return void - This function doesn't return anything.
    */
    void print(std::ostream& os) const override;

    /** \brief Function for displaying CompositeSquareMatrix as a string in proper format
    * \return std::string ss - CompositeSquareMatrix as a properly formatted string
    */
    std::string toString() const override;

    /** \brief Function for valuating the Elements of the CompositeSquareMatrix
    * \param Valuation& valu - std::map<char, int> for storing values for the encapsulated variables
    * \throw std::invalid_argument("Var value not in Valuation valu.") - if encapsulated character in any of the Elements has no matching integer value in Valuation valu
    * \return ConcreteSquareMatrix - ConcreteSquareMatrix in which all of the CompositeSquareMatrix's VariableElements's character values have been replaced by integer values according to Valuation valu
    */
    ConcreteSquareMatrix evaluate(const Valuation& valu) const override;
};

/** \brief << operator for outputting CompositeSquareMatrix.
* \param std::ostream& os - Outputstream for the output
* \param CompositeSquareMatrix& m - CompositeSquareMatrix which to output
* \return std::ostream& os - The outputstream for the output with the CompositeSquareMatrix inside
*/
std::ostream& operator<<(std::ostream& os, CompositeSquareMatrix& m);

#endif // COMPOSITEMATRIX_H_INCLUDED


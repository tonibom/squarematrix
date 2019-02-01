/** \file concretematrix.h
*/

#ifndef CONCRETESQUAREMATRIX_H_INCLUDED
#define CONCRETESQUAREMATRIX_H_INCLUDED

#include "squarematrix.h"
#include "element.h"
#include "catch.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>
#include <numeric>
#include <algorithm>


/** \class ConcreteSquareMatrix
* \brief This is a class for storing and handling squarematrixes with integer values.
*/
class ConcreteSquareMatrix : public SquareMatrix {

private:

    /** \brief The dimension length of the squarematrix
    */
    unsigned int n;

    /** \brief Two dimensional vector to hold the pointers to the IntElements
    */
    std::vector< std::vector<uniq_intelem_ptr> > elements;

public:

    /** \brief Constructor without parameters
    * This will construct a ConcreteSquareMatrix with the size of 0.
    */
    ConcreteSquareMatrix();

    /** \brief Constructor which constructs a ConcreteSquareMatrix with std::string as a specification
    * \throw std::invalid_argument("Invalid init string") - if the parameter string wasn't a valid squarematrix
    * \param std::string& str - string according to which the ConcreteSquareMatrix will be constructed
    */
    ConcreteSquareMatrix(const std::string& str);

    /** \brief Constructor which duplicates another ConcreteSquareMatrix
    * \param ConcreteSquareMatrix& m - ConcreteSquareMatrix which is to be duplicated
    */
    ConcreteSquareMatrix(const ConcreteSquareMatrix& m);

    /** \brief Move constructor which steals another ConcreteSquareMatrix's values
    * \param ConcreteSquareMatrix&& m - temporary ConcreteSquareMatrix from which values are to be stolen
    */
    ConcreteSquareMatrix(ConcreteSquareMatrix&& m);

    /** \brief Default destructor
    */
    ~ConcreteSquareMatrix() = default;

    /** \brief = operator for assigning a ConcreteSquareMatrix over another ConcreteSquareMatrix
    * \param ConcreteSquareMatrix& m - The ConcreteSquareMatrix which is to be assigned
    * \return ConcreteSquareMatrix& - The resulting ConcreteSquareMatrix
    */
    ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix& m);

    /** \brief = operator for assigning a temporary ConcreteSquareMatrix's values over another ConcreteSquareMatrix's
    * \param ConcreteSquareMatrix&& m - Temporary ConcreteSquareMatrix which values are to be used in assignment
    * \return ConcreteSquareMatrix& - The resulting ConcreteSquareMatrix
    */
    ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&& m);

    /** \brief Function for cloning a ConcreteSquareMatrix
    * \return SquareMatrix *pMatrix - Pointer variable that points to a fresh copy of the ConcreteSquareMatrix
    */
    SquareMatrix* clone() const override;

    /** \brief Function for transposing a ConcreteSquareMatrix
    * \return ConcreteSquareMatrix temp - Transposed ConcreteSquareMatrix
    */
    ConcreteSquareMatrix transpose() const;

    /** \brief += operator for calculating the addition of two ConcreteSquareMatrixes
    * \param ConcreteSquareMatrix& m - The other ConcreteSquareMatrix
    * \throw std::invalid_argument("Invalid init matrixes") - if parameter ConcreteSquareMatrix is not of the same dimensions as the other ConcreteSquareMatrix
    * \return ConcreteSquareMatrix& - The resulting ConcreteSquareMatrix
    */
    ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix& m);

    /** \brief -= operator for calculating the subtraction of two ConcreteSquareMatrixes
    * \param ConcreteSquareMatrix& m - The other ConcreteSquareMatrix
    * \throw std::invalid_argument("Invalid init matrixes") - if parameter ConcreteSquareMatrix is not of the same dimensions as the other ConcreteSquareMatrix
    * \return ConcreteSquareMatrix& - The resulting ConcreteSquareMatrix
    */
    ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix& m);

    /** \brief *= operator for calculating the multiplication of two ConcreteSquareMatrixes
    * \param SquareMatrix& m - The other ConcreteSquareMatrix
    * \throw std::invalid_argument("Invalid init matrixes") - if parameter ConcreteSquareMatrix is not of the same dimensions as the other ConcreteSquareMatrix
    * \return ConcreteSquareMatrix& - The resulting ConcreteSquareMatrix
    */
    ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix& m);

    /** \brief == operator for comparing two ConcreteSquareMatrixes
    * \param ConcreteSquareMatrix& m - The other ConcreteSquareMatrix
    * \return bool - true if ConcreteSquareMatrixes are equal, false if they're not
    */
    bool operator==(const ConcreteSquareMatrix& m) const;

    /** \brief Function for printing ConcreteSquareMatrix
    * \param std::ostream& os - Outputstream for the output
    * \return void - This function doesn't return anything.
    */
    void print(std::ostream& os) const override;

    /** \brief Function for displaying ConcreteSquareMatrix as a string in proper format
    * \return std::string ss - ConcreteSquareMatrix as a properly formatted string
    */
    std::string toString() const override;

    /** \brief Function for valuating the Elements of the ConcreteSquareMatrix
    * \param Valuation& valu - std::map<char, int> for storing values for the encapsulated variables
    * \throw std::invalid_argument("Var value not in Valuation valu.") - if encapsulated character in any of the Elements has no matching integer value in Valuation valu
    * \return ConcreteSquareMatrix - ConcreteSquareMatrix in which all of the ConcreteSquareMatrix's Element values have been replaced by integer values according to Valuation valu
    */
    ConcreteSquareMatrix evaluate(const Valuation& valu) const override;
};

/** \brief + operator for calculating the addition of two ConcreteSquareMatrix.
* \param ConcreteSquareMatrix& m1 - The first ConcreteSquareMatrix
* \param ConcreteSquareMatrix& m2 - The second ConcreteSquareMatrix
* \return ConcreteSquareMatrix temp - The resulting value
*/
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);

/** \brief - operator for calculating the subtraction of two ConcreteSquareMatrix.
* \param ConcreteSquareMatrix& m1 - The first ConcreteSquareMatrix
* \param ConcreteSquareMatrix& m2 - The second ConcreteSquareMatrix
* \return ConcreteSquareMatrix temp - The resulting value
*/
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);

/** \brief * operator for calculating the multiplication of two ConcreteSquareMatrix.
* \param ConcreteSquareMatrix& m1 - The first ConcreteSquareMatrix
* \param ConcreteSquareMatrix& m2 - The second ConcreteSquareMatrix
* \return ConcreteSquareMatrix temp - The resulting value
*/
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);

/** \brief << operator for outputting ConcreteSquareMatrix.
* \param std::ostream& os - Outputstream for the output
* \param ConcreteSquareMatrix& m - ConcreteSquareMatrix which to output
* \return std::ostream& os - The outputstream for the output with the ConcreteSquareMatrix inside
*/
std::ostream& operator<<(std::ostream& os, ConcreteSquareMatrix& m);

#endif // CONCRETEMATRIX_H_INCLUDED



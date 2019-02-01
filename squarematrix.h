/** \file squarematrix.h
*/
#ifndef SQUAREMATRIX_H_INCLUDED
#define SQUAREMATRIX_H_INCLUDED

#include "element.h"

#include <string>
#include <ostream>

class ConcreteSquareMatrix;

/** \class SquareMatrix
* \brief This is an abstract class.
*/
class SquareMatrix{

public:

    /** \brief destructor
    */
    virtual ~SquareMatrix(){};

    /** \brief Abstract function for cloning SquareMatrixes
    * \return SquareMatrix *pElem - Pointer variable that points to a fresh copy of the SquareMatrix
    */
    virtual SquareMatrix* clone() const = 0;

    /** \brief Abstract function for printing SquareMatrixes
    * \return void - This function doesn't return anything.
    */
    virtual void print(std::ostream& os) const = 0;

    /** \brief Abstract function for displaying SquareMatrix as a string.
    * \return std::string ss - SquareMatrix as a properly formatted string
    */
    virtual std::string toString() const = 0;

    /** \brief Abstract function for valuating SquareMatrixes
    * \param Valuation& valu - std::map<char, int> for storing values for the encapsulated variables
    * \throw std::invalid_argument("Var value not in Valuation valu.") - if encapsulated character in any of the Elements has no matching integer value in Valuation valu
    * \return ConcreteSquareMatrix - ConcreteSquareMatrix in which all of the SquareMatrix's Elements' character values have been replaced by integer values according to Valuation valu
    */
    virtual ConcreteSquareMatrix evaluate(const Valuation& valu) const = 0;
};

/** \brief Shorter version of unique SquareMatrix pointer initialization
*/
using uniq_sqm_ptr = std::unique_ptr<SquareMatrix>;

/** \brief << operator for outputting SquareMatrix.
* \param std::ostream& os - Outputstream for the output
* \param SquareMatrix& m - SquareMatrix which to output
* \return std::ostream& os - The outputstream for the output with the SquareMatrix inside
*/
std::ostream& operator<<(std::ostream& os, SquareMatrix& m);

#endif // SQUAREMATRIX_H_INCLUDED


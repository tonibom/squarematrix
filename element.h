/** \file element.h
*/

#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include "catch.hpp"
#include "valuation.h"

#include <sstream>
#include <map>
#include <iostream>

/** \class Element
* \brief This is an abstract class.
*/
class Element{

public:

    /** \brief destructor
    */
    virtual ~Element(){};

    /** \brief Abstract function for cloning Elements
    * \return Element *pElem - Pointer variable that points to a fresh copy of the Element
    */
    virtual Element* clone() const = 0;

    /** \brief Abstract function for displaying Element as a string.
    * \return std::string ss - Element as a properly formatted string
    */
    virtual std::string toString() const = 0;

    /** \brief Abstract function for valuating Elements
    * \param Valuation& valu - std::map<char, int> for storing values for the encapsulated variables
    * \return int val - Integer value stored either as itself or as a char variable and valuated according to Valuation& valu
    */
    virtual int evaluate(const Valuation& valu) const = 0;

};





/** \class IntElement
* \brief This is an Element subclass that encapsulates an integer value.
*/
class IntElement : public Element{

private:

    /** \brief Integer value held in class IntElement
    */
    int val;

public:

    /** \brief Constructor without parameters
    * This will construct an IntElement with int val set to 0.
    */
    IntElement();

    /** \brief Constructor with a parameter
    * \param int v - The value for the int val -attribute
    */
    IntElement(int v);

    /** \brief Default destructor
    */
    ~IntElement() = default;

    /** \brief Getter for the encapsulated integer value.
    * \return int val - The value stored in the private integer
    */
    int getVal() const;

    /** \brief Setter for the encapsulated integer value.
    * \param int v - New value to be set for the private integer
    * \return void - This function doesn't return anything.
    */
    void setVal(int v);

    /** \brief += operator for calculating the addition of two IntElements
    * \param IntElement& i - The other IntElement
    * \return IntElement& - The resulting IntElement
    */
    IntElement& operator+=(const IntElement& i);

    /** \brief -= operator for calculating the subtraction of two IntElements.
    * \param IntElement& i - The other IntElement
    * \return IntElement& - The resulting IntElement
    */
    IntElement& operator-=(const IntElement& i);

    /** \brief *= operator for calculating the multiplication of two IntElements.
    * \param IntElement& i - The other IntElement
    * \return IntElement& - The resulting IntElement
    */
    IntElement& operator*=(const IntElement& i);

    /** \brief == operator for comparing two IntElements
    * \param IntElement& i - The other IntElement
    * \return bool - True if both IntElements have the same value in the val attribute. Else returns false.
    */
    bool operator==(const IntElement& i) const;

    /** \brief + operator for calculating the addition of two IntElements.
    * \param IntElement& m - The other IntElement
    * \return IntElement ielem - The resulting value
    */
    IntElement operator+(const IntElement& m);

    /** \brief - operator for calculating the subtraction of two IntElements.
    * \param IntElement& m - The other IntElement
    * \return IntElement ielem - The resulting value
    */
    IntElement operator-(const IntElement& m);

    /** \brief * operator for calculating the multiplication of two IntElements.
    * \param IntElement& m - The other IntElement
    * \return IntElement ielem - The resulting value
    */
    IntElement operator*(const IntElement& m);

    /** \brief Function for displaying IntElement as a string.
    * \return std::string ss - IntElement as a properly formatted string
    */
    std::string toString() const;

    /** \brief Function for cloning an IntElement
    * \return IntElement *pElem - Pointer variable that points to a fresh copy of the IntElement
    */
    Element* clone() const;

    /** \brief Function for valuating IntElements
    * \param Valuation& valu - std::map<char, int> for storing values for the encapsulated variables
    * \return int val - The integer value encapsulated in the IntElement class
    */
    int evaluate(const Valuation& valu) const;
};


/** \brief << operator for outputting IntElement.
* \param std::ostream& os - Outputstream for the output
* \param IntElement& m - IntElement which to output
* \return std::ostream& os - The outputstream for the output with the IntElement inside
*/
std::ostream& operator<<(std::ostream& os, IntElement& m);




/** \class VariableElement
* This is an Element subclass that encapsulates a character value.
*/
class VariableElement : public Element{

private:

    /** \brief Character value held in class VariableElement
    */
    char var;

public:

    /** \brief Constructor without parameters
    * This will construct a VariableElement with char var set to 'g'.
    */
    VariableElement();

    /** \brief Constructor with a parameter
    * \param char v - The value for the char var -attribute
    */
    VariableElement(char v);

    /** \brief Default destructor
    */
    ~VariableElement() = default;

    /** \brief Getter for the encapsulated character value.
    * \return char var - The value stored in the private character
    */
    char getVal() const;

    /** \brief Setter for the encapsulated character value.
    * \param char var - New value to be set for the private character
    * \return void - This function doesn't return anything.
    */
    void setVal(int v);

    /** \brief Function for cloning a VariableElement
    * \return VariableElement *pElem - Pointer variable that points to a fresh copy of the VariableElement
    */
    Element* clone() const;

    /** \brief Function for displaying VariableElement as a string.
    * \return std::string ss - VariableElement as a properly formatted string
    */
    std::string toString() const;

    /** \brief Function for valuating VariableElements
    * \param Valuation& valu - std::map<char, int> for storing values for the encapsulated variables
    * \throw std::invalid_argument("Var value not in Valuation valu.") - if encapsulated character has no matching integer value in Valuation valu
    * \return int val - The integer value of the encapsulated character in the VariableElement class according to Valuation& valu
    */
    int evaluate(const Valuation& valu) const;

    /** \brief == operator for comparing two VariableElements
    * \param VariableElement& i - The other VariableElement
    * \return bool - True if both VariableElements have the same value in the var attribute. Else returns false.
    */
    bool operator==(const VariableElement& i) const;
};

/** \brief << operator for outputting VariableElement.
* \param std::ostream& os - Outputstream for the output
* \param VariableElement& m - VariableElement which to output
* \return std::ostream& os - The outputstream for the output with the VariableElement inside
*/
std::ostream& operator<<(std::ostream& os, VariableElement& m);

/** \brief Shorter version of unique IntElement pointer initialization
*/
typedef std::unique_ptr<IntElement> uniq_intelem_ptr;

/** \brief Shorter version of unique Element pointer initialization
*/
typedef std::unique_ptr<Element> uniq_elem_ptr;

#endif // ELEMENT_H_INCLUDED



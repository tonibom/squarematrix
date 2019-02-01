#include "element.h"
#include "catch.hpp"

#include <iostream>

TEST_CASE("IntElement checking", "[element][intelement]"){

    IntElement ielem(5);
    CHECK(ielem.getVal() == 5);
    ielem.setVal(10);
    CHECK(ielem.getVal() == 10);
    CHECK_FALSE(ielem.getVal() == 5);

    IntElement ielem2(15);
    ielem += ielem2;
    CHECK(ielem.getVal() == 25);

    ielem -= ielem2;
    CHECK(ielem.getVal() == 10);

    ielem *= ielem2;
    CHECK(ielem.getVal() == 150);

    ielem2 = ielem2 + ielem;
    CHECK(ielem2.getVal() == 165);

    ielem2 = ielem2 - ielem;
    CHECK(ielem2.getVal() == 15);

    ielem = ielem - 145;
    CHECK((ielem2 * ielem).getVal() == 75);

    CHECK_FALSE(ielem == ielem2);
    IntElement ielem3(5);
    CHECK(ielem == ielem3);
    ielem3.setVal(1000);
    CHECK(ielem3.getVal() == 1000);

    CHECK(ielem.toString() == "5");
    std::cout << ielem << std::endl;
    IntElement *ielem4 = new IntElement(ielem);
    delete ielem4;

    IntElement ielem5;
    CHECK(ielem5.getVal() == 0);

}

TEST_CASE("VariableElement checking", "[element][variableelement]"){

    Valuation valu;

    valu.insert(std::pair<char,int>('x',10));
    valu.insert(std::pair<char,int>('y',50));
    valu.insert(std::pair<char,int>('z',300));

    VariableElement velemEmpty;
    VariableElement velem('x');
    CHECK(velem.toString() == "x");
    CHECK(velem.getVal() == 'x');

    VariableElement velemCopy(velem);
    CHECK(velemCopy.toString() == "x");
    CHECK(velemCopy.getVal() == 'x');

    VariableElement velemCopy2(std::move(velemCopy));
    CHECK(velemCopy2.toString() == "x");
    CHECK(velemCopy2.getVal() == 'x');
    CHECK(velem == velemCopy2);
    CHECK(velem.evaluate(valu) == velemCopy2.evaluate(valu));
    VariableElement velem2('z');
    velemCopy2.setVal('y');
    CHECK(velemCopy2.evaluate(valu) == 50);
    CHECK_FALSE(velemCopy2.evaluate(valu) == 10);

    CHECK(velem.evaluate(valu) == 10);
    CHECK_FALSE(velem == velem2);

    VariableElement velemFail('b');
    CHECK_THROWS(velemFail.evaluate(valu));
}





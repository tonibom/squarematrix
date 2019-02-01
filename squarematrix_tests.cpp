#define CATCH_CONFIG_MAIN

#include "concretematrix.h"
#include "symbolicmatrix.h"
#include "compositematrix.h"
#include "element.h"
#include "catch.hpp"


//These includes are required for gcov test coverage testing if TDM compiler is used.

//#include "concretematrix.cpp"
//#include "compositematrix.cpp"
//#include "symbolicmatrix.cpp"
//#include "element.cpp"
//#include "element_tests.cpp"




TEST_CASE("ConcreteSquareMatrix checking", "[concrete][matrix]"){
    ConcreteSquareMatrix matrix;
    CHECK(matrix.toString() == "[]");

    ConcreteSquareMatrix matrix2("[[1,2][3,4]]");
    CHECK(matrix2.toString() == "[[1,2][3,4]]");
    std::cout << matrix2 << std::endl;

    ConcreteSquareMatrix matrix3(matrix2);
    CHECK(matrix3.toString() == "[[1,2][3,4]]");

    CHECK(matrix2 == matrix3);

    ConcreteSquareMatrix matrix4("[[1,2,3][4,5,6][7,8,9]]");
    matrix4 = matrix4.transpose();
    CHECK(matrix4.toString() == "[[1,4,7][2,5,8][3,6,9]]");
    matrix4.print(std::cout);

    ConcreteSquareMatrix matrix5("[[9,4][2,7]]");
    matrix3 += matrix5;
    CHECK(matrix3.toString() == "[[10,6][5,11]]");

    matrix3 -= matrix2;
    CHECK(matrix3.toString() == "[[9,4][2,7]]");

    ConcreteSquareMatrix matrix6("[[2,4,5][7,4,9][1,12,3]]");
    ConcreteSquareMatrix matrix7("[[6,4,10][8,12,2][3,7,11]]");
    CHECK_FALSE(matrix6 == matrix7);

    matrix6 *= matrix7;
    CHECK(matrix6.toString() == "[[59,91,83][101,139,177][111,169,67]]");
    matrix6 = matrix7;
    CHECK(matrix6.toString() == "[[6,4,10][8,12,2][3,7,11]]");

    ConcreteSquareMatrix *matrix8 = new ConcreteSquareMatrix("[[1,2][3,4]]");
    CHECK(matrix8->toString() == "[[1,2][3,4]]");
    delete matrix8;

    ConcreteSquareMatrix matrix9(ConcreteSquareMatrix("[[1,2][3,4]]"));
    ConcreteSquareMatrix matrix10 = std::move(matrix9);
    CHECK(matrix9.toString() == "[]");
    CHECK(matrix10.toString() == "[[1,2][3,4]]");

    CHECK_THROWS(matrix3 += matrix4);
    CHECK_THROWS(matrix3 -= matrix4);
    CHECK_THROWS(matrix3 *= matrix4);

    CHECK_THROWS(ConcreteSquareMatrix failMatrix("][1,1][1,1]]"));
    CHECK_THROWS(ConcreteSquareMatrix failMatrix("[]1,1][1,1]]"));
    CHECK_THROWS(ConcreteSquareMatrix failMatrix("[[a,1][1,1]]"));
    CHECK_THROWS(ConcreteSquareMatrix failMatrix("[[1:1][1,1]]"));
    CHECK_THROWS(ConcreteSquareMatrix failMatrix("[[1,1][1,1]["));
    CHECK_THROWS(ConcreteSquareMatrix failMatrix("[[1,1,1][1,1][1,1,1]]"));
    CHECK_THROWS(ConcreteSquareMatrix failMatrix("[[1,1][1,1]]AAAAAAAAAAAAAAAAAAA"));

}

TEST_CASE("SymbolicSquareMatrix checking", "[symbolic][matrix]"){

    SymbolicSquareMatrix ssmEmpty;
    CHECK(ssmEmpty.toString() == "[]");

    SymbolicSquareMatrix ssm("[[1,x][2,y]]");
    ssm.print(std::cout);
    CHECK(ssm.toString() == "[[1,x][2,y]]");

    SymbolicSquareMatrix ssmCopy(ssm);
    CHECK(ssmCopy.toString() == "[[1,x][2,y]]");
    CHECK(ssm == ssmCopy);

    SymbolicSquareMatrix ssmCopy2(std::move(ssmCopy));
    CHECK(ssmCopy2.toString() == "[[1,x][2,y]]");
    CHECK(ssmCopy.toString() == "[]");
    CHECK(ssm == ssmCopy2);

    SymbolicSquareMatrix ssm2("[[5,7][8,y]]");
    SymbolicSquareMatrix ssm3("[[10,y][5,12]]");
    ssm2 = ssm3;
    CHECK(ssm2.toString() == "[[10,y][5,12]]");
    ssm2 = ssm2.transpose();
    CHECK(ssm2.toString() == "[[10,5][y,12]]");

    SymbolicSquareMatrix ssm4 = SymbolicSquareMatrix("[[x,2][y,4]]");
    SymbolicSquareMatrix ssm5 = std::move(ssm4);
    CHECK(ssm5.toString() == "[[x,2][y,4]]");
    CHECK(ssm4.toString() == "[]");
    CHECK_FALSE(ssm2 == ssm3);

    Valuation valu;
    valu.insert(std::pair<char,int>('x',10));
    valu.insert(std::pair<char,int>('y',50));
    valu.insert(std::pair<char,int>('z',300));

    ConcreteSquareMatrix cosm;
    cosm = ssm5.evaluate(valu);
    CHECK(cosm.toString() == "[[10,2][50,4]]");

    std::cout << ssm5 << std::endl;


    CHECK_THROWS(SymbolicSquareMatrix failMatrix("][1,z][1,1]]"));
    CHECK_THROWS(SymbolicSquareMatrix failMatrix("[]1,1][x,1]]"));
    CHECK_THROWS(SymbolicSquareMatrix failMatrix("[[a,d][%,1]]"));
    CHECK_THROWS(SymbolicSquareMatrix failMatrix("[[1:1][1,1]]"));
    CHECK_THROWS(SymbolicSquareMatrix failMatrix("[[1,h][1,1]["));
    CHECK_THROWS(SymbolicSquareMatrix failMatrix("[[1,1,1][s,1][j,1,l]]"));
    CHECK_THROWS(SymbolicSquareMatrix failMatrix("[[1,1][1,1]]AAAAAAAAAAAAAAAAAAA"));
}



TEST_CASE("CompositeSquareMatrix checking", "[composite][matrix]"){

    ConcreteSquareMatrix csm1("[[1,2][3,4]]");
    ConcreteSquareMatrix csm2("[[7,4][-9,1]]");
    ConcreteSquareMatrix csm3("[[9,0][6,8]]");

    SymbolicSquareMatrix ssm1("[[1,x][y,4]]");
    SymbolicSquareMatrix ssm2("[[y,10][z,-5]]");
    SymbolicSquareMatrix ssm3("[[5,6][14,z]]");

    CompositeSquareMatrix csmPlus(csm1, ssm1, std::plus<ConcreteSquareMatrix>(), '+');
    CompositeSquareMatrix csmMinus(csm2, ssm2, std::minus<ConcreteSquareMatrix>(), '-');
    CompositeSquareMatrix csmMultiply(csm3, ssm3, std::multiplies<ConcreteSquareMatrix>(), '*');

    Valuation valu;
    valu.insert(std::pair<char,int>('x',10));
    valu.insert(std::pair<char,int>('y',50));
    valu.insert(std::pair<char,int>('z',300));

    CHECK(csmPlus.evaluate(valu).toString() == "[[2,12][53,8]]");
    CHECK(csmMinus.evaluate(valu).toString() == "[[-43,-6][-309,6]]");
    CHECK(csmMultiply.evaluate(valu).toString() == "[[45,54][142,2436]]");

    CompositeSquareMatrix csmCopy(csmPlus);
    CHECK(csmCopy.toString() == "([[1,2][3,4]]+[[1,x][y,4]])");
    CHECK(csmCopy.toString() == csmPlus.toString());

    CompositeSquareMatrix csmCopy2(std::move(csmCopy));
    CHECK(csmCopy2.toString() == "([[1,2][3,4]]+[[1,x][y,4]])");
    CHECK(csmCopy2.toString() == csmPlus.toString());

    csmCopy2.print(std::cout);

    CompositeSquareMatrix csmAssign(csm2, ssm2, std::minus<ConcreteSquareMatrix>(), '-');
    csmAssign = csmMultiply;
    CHECK(csmAssign.evaluate(valu).toString() == "[[45,54][142,2436]]");

    CompositeSquareMatrix csmAssign2 = CompositeSquareMatrix(csm2, ssm2, std::minus<ConcreteSquareMatrix>(), '-');
    CompositeSquareMatrix csmAssign3(csmAssign);
    csmAssign3 = std::move(CompositeSquareMatrix(ConcreteSquareMatrix("[[7,4][-9,1]]"), SymbolicSquareMatrix("[[y,10][z,-5]]"), std::minus<ConcreteSquareMatrix>(), '-'));
    CHECK(csmAssign3.evaluate(valu).toString() == "[[-43,-6][-309,6]]");

    CHECK(csmAssign3.clone()->toString() == "([[7,4][-9,1]]-[[y,10][z,-5]])");
    CHECK(csmAssign3.evaluate(valu).toString() == "[[-43,-6][-309,6]]");

    std::cout << csmPlus << std::endl;

}


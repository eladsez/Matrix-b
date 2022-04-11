/**
 * @file Test.cpp
 * @author Elad Sezanayev
 * @brief Test cases for the matrix assignment
 * @date 2022-04
 */

#include "doctest.h"
#include "sources/Matrix.hpp"
#include <iostream>
#include <vector>

using namespace zich;
using namespace std;

TEST_CASE ("invalid inputs") {

            SUBCASE("invalid Matrix size for specific operators") {
        vector<double> vals1 = {2, 2, 2, 1, 1, 1, 3, 3, 3};
        Matrix mat1(vals1, 3, 3);
        vector<double> vals2 = {2, 2, 2, 1, 1, 1, 3, 3, 3, 4, 4, 4};
        Matrix mat2(vals2, 4, 3);
        bool none;
        CHECK_THROWS(mat1 + mat2);
        CHECK_THROWS(mat1 - mat2);
        CHECK_THROWS(mat1 * mat2);
        CHECK_THROWS(mat1 += mat2);
        CHECK_THROWS(mat1 -= mat2);
        CHECK_THROWS(mat1 *= mat2);
        CHECK_THROWS(none = mat1 == mat2); // the none is because tidy yelling
        CHECK_THROWS(none = mat1 != mat2);
        CHECK_THROWS(none = mat1 > mat2);
        CHECK_THROWS(none = mat1 < mat2);
        CHECK_THROWS(none = mat1 <= mat2);
        CHECK_THROWS(none = mat1 >= mat2);
    }
}

TEST_CASE ("valid inputs") {

    SUBCASE("operators ERROR deducting") {
        vector<double> vals1 = {2, 2, 2, 1, 1, 1, 3, 3, 3};
        Matrix mat1(vals1, 3, 3);
        vector<double> vals2 = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        Matrix mat2(vals2, 3, 3);
        bool none;
        CHECK_NOTHROW(mat1 + mat2);
        CHECK_NOTHROW(mat1 - mat2);
        CHECK_NOTHROW(mat1 * mat2);
        CHECK_NOTHROW(mat1 += mat2);
        CHECK_NOTHROW(mat1 -= mat2);
        CHECK_NOTHROW(mat1 *= mat2);
        CHECK_NOTHROW(none = mat1 == mat2); // the none because tidy is yelling
        CHECK_NOTHROW(none = mat1 != mat2);
        CHECK_NOTHROW(none = mat1 > mat2);
        CHECK_NOTHROW(none = mat1 < mat2);
        CHECK_NOTHROW(none = mat1 <= mat2);
        CHECK_NOTHROW(none = mat1 >= mat2);
    }


    SUBCASE("Operators correctness check") {
        vector<double> vals1 = {2, 2, 2, 2, 2, 2, 2, 2, 2};
        Matrix mat1(vals1, 3, 3);
        vector<double> vals2 = {3, 3, 3, 3, 3, 3, 3, 3, 3};
        Matrix mat2(vals2, 3, 3);

        CHECK(mat1 <= mat2);
        CHECK(mat2 >= mat1);
        CHECK(mat1 != mat2);
        CHECK(++mat1 == mat2);
        CHECK(mat1++ == mat2); // mat1 should fill with 4 after the postfix operator
        mat1 *= 3;
        mat2 *= 4;
        CHECK(mat1 == mat2); // they both fill with 6
        CHECK(mat1 * 3 == 3 * mat2);
        CHECK(mat1 + mat2 == mat2 + mat1);
        CHECK(mat1 - mat2 == mat2 - mat1); // both sides fill with 0

        vector<double> mul1 = {1, 2, 3, 4, 5, 6};
        vector<double> mul2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Matrix mat_mul1(mul1, 2, 3);
        Matrix mat_mul2(mul2, 3, 3);

        vector<double> res1 = {30, 36, 42, 66, 81, 96};
        Matrix mat_res1(res1, 2, 3);
        CHECK(mat_mul1 * mat_mul2 == mat_res1);

        vector<double> res2 = {468, 576, 684, 1062, 1305, 1548};
        CHECK(mat_res1 * mat_mul2 == Matrix(res2, 2, 3));
        mat_res1 *= mat_mul2;
        CHECK(mat_res1 == Matrix(res2, 2, 3));


    }
}
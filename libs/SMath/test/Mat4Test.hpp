#ifndef MAT4TEST_HH
#define MAT4TEST_HH

#include <gtest/gtest.h>
#include "../include/mat4.hpp"
#include "iostream"

// Test default constructor
TEST(Mat4Test, Mat4TestDefaultConstructor) {
    mat4 result;
    for (int col = 0; col < MAT4_COLUMN_SIZE; col++) {
        for (int row = 0; row < MAT4_ROW_SIZE; row++) {
            EXPECT_FLOAT_EQ(result[col][row], 0.0f);
        }
    }
}

// Test identity matrix constructor
TEST(Mat4Test, Mat4TestIdentityConstructor) {
    mat4 result(1.0f);
    for (int col = 0; col < MAT4_COLUMN_SIZE; col++) {
        for (int row = 0; row < MAT4_ROW_SIZE; row++) {
            if (col == row){
                EXPECT_FLOAT_EQ(result[col][row], 1.0f);
            } else {
                EXPECT_FLOAT_EQ(result[col][row], 0.0f);
            }
            
        }
    }
}

// Test copy constructor
TEST(Mat4Test, Mat4TestCopyConstructor) {
    float m[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                   9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

    mat4 expected {m};
    mat4 result {expected};
    for (int col = 0; col < MAT4_COLUMN_SIZE; col++) {
        for (int row = 0; row < MAT4_ROW_SIZE; row++) {
            EXPECT_FLOAT_EQ(result[col][row], expected[col][row]);
        }
    }
}

// Test assignment operator
TEST(Mat4Test, Mat4TestAssignmentOperator) {
    float m[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                   9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    mat4 expected {m};
    mat4 result;
    result = expected;
    for (int col = 0; col < MAT4_COLUMN_SIZE; col++) {
        for (int row = 0; row < MAT4_ROW_SIZE; row++) {
            EXPECT_FLOAT_EQ(result[col][row], expected[col][row]);
        }
    }
}

// Test element access operator
TEST(Mat4Test, Mat4TestElementAccessOperator) {
    float expected[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                   9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};

    mat4 result {expected};
    for (int col = 0; col < MAT4_COLUMN_SIZE; col++) {
        for (int row = 0; row < MAT4_ROW_SIZE; row++) {
            EXPECT_FLOAT_EQ(result[col][row], expected[row * 4 + col]);
        }
    }
}

// Test scalar multiplication
TEST(Mat4Test, Mat4TestScalarMultiplication) {
    float expected[] = {2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f,
                      18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f};
    
    float m[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                   9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    float skalar = 2.0f;

    mat4 m1 {m};
    mat4 result = m1 * skalar;
    for (int col = 0; col < MAT4_COLUMN_SIZE; col++) {
        for (int row = 0; row < MAT4_ROW_SIZE; row++) {
            EXPECT_FLOAT_EQ(result[col][row], expected[row * 4 + col]);
        }
    }
}

// Test matrix multiplication
TEST(Mat4Test, Mat4TestMatrixMultiplication) {
    float expected[] = {215, 242, 269, 296, 125, 138, 151, 164,
                            67, 78, 89, 100, 111, 130, 149, 168};

    float mt1[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                   9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    float mt2[] = {4.0f, 8.0f, 6.0f, 9.0f, 1.0f, 3.0f, 2.0f, 7.0f,
                    5.0f, 0.0f, 4.0f, 2.0f, 9.0f, 3.0f, 1.0f, 6.0f};
    mat4 m1 {mt1};
    mat4 m2 {mt2};
    mat4 result = m1 * m2;
    for (int col = 0; col < MAT4_COLUMN_SIZE; col++) {
        for (int row = 0; row < MAT4_ROW_SIZE; row++) {
            EXPECT_FLOAT_EQ(result[col][row], expected[row * 4 + col]);
        }
    }
}

#endif
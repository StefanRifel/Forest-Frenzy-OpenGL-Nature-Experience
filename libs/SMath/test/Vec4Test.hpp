#ifndef VEC4TEST_HH
#define VEC4TEST_HH

#include <gtest/gtest.h>
#include "../include/vec4.hpp"

// Test default constructor
TEST(Vec4Test, Vec4TestDefaultConstructor) {
    vec4 v;
    EXPECT_FLOAT_EQ(v.x(), 0.0f);
    EXPECT_FLOAT_EQ(v.y(), 0.0f);
    EXPECT_FLOAT_EQ(v.z(), 0.0f);
    EXPECT_FLOAT_EQ(v.w(), 0.0f);
}

// Test parameterized constructor
TEST(Vec4Test, Vec4TestParameterizedConstructor) {
    vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
    EXPECT_FLOAT_EQ(v.w(), 4.0f);
}

// Test copy constructor
TEST(Vec4Test, Vec4TestCopyConstructor) {
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(v1);
    EXPECT_FLOAT_EQ(v2.x(), 1.0f);
    EXPECT_FLOAT_EQ(v2.y(), 2.0f);
    EXPECT_FLOAT_EQ(v2.z(), 3.0f);
    EXPECT_FLOAT_EQ(v2.w(), 4.0f);
}

// Test assignment operator
TEST(Vec4Test, Vec4TestAssignmentOperator) {
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2;
    v2 = v1;
    EXPECT_FLOAT_EQ(v2.x(), 1.0f);
    EXPECT_FLOAT_EQ(v2.y(), 2.0f);
    EXPECT_FLOAT_EQ(v2.z(), 3.0f);
    EXPECT_FLOAT_EQ(v2.w(), 4.0f);
}

// Test element access operator
TEST(Vec4Test, Vec4TestElementAccessOperator) {
    vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
    EXPECT_FLOAT_EQ(v[3], 4.0f);
}

// Test equality operator
TEST(Vec4Test, Vec4TestEqualityOperator) {
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_TRUE(v1 == v2);
}

// Test inequality operator
TEST(Vec4Test, Vec4TestInequalityOperator) {
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(4.0f, 5.0f, 6.0f, 7.0f);
    EXPECT_TRUE(v1 != v2);
}

// Test addition operator
TEST(Vec4Test, Vec4TestAdditionOperator) {
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(4.0f, 5.0f, 6.0f, 7.0f);
    vec4 v3 = v1 + v2;
    EXPECT_FLOAT_EQ(v3.x(), 5.0f);
    EXPECT_FLOAT_EQ(v3.y(), 7.0f);
    EXPECT_FLOAT_EQ(v3.z(), 9.0f);
    EXPECT_FLOAT_EQ(v3.w(), 11.0f);
}

// Test subtraction operator
TEST(Vec4Test, Vec4TestSubtractionOperator) {
    vec4 v1(4.0f, 5.0f, 6.0f, 7.0f);
    vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v3 = v1 - v2;
    EXPECT_FLOAT_EQ(v3.x(), 3.0f);
    EXPECT_FLOAT_EQ(v3.y(), 3.0f);
    EXPECT_FLOAT_EQ(v3.z(), 3.0f);
    EXPECT_FLOAT_EQ(v3.w(), 3.0f);
}

// Test scalar multiplication operator
TEST(Vec4Test, Vec4TestScalarMultiplicationOperator) {
    vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2 = v * 2.0f;
    EXPECT_FLOAT_EQ(v2.x(), 2.0f);
    EXPECT_FLOAT_EQ(v2.y(), 4.0f);
    EXPECT_FLOAT_EQ(v2.z(), 6.0f);
    EXPECT_FLOAT_EQ(v2.w(), 8.0f);
}

// Test += operator
TEST(Vec4Test, Vec4TestAdditionAssignmentOperator) {
    vec4 v1(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 v2(4.0f, 5.0f, 6.0f, 7.0f);
    v1 += v2;
    EXPECT_FLOAT_EQ(v1.x(), 5.0f);
    EXPECT_FLOAT_EQ(v1.y(), 7.0f);
    EXPECT_FLOAT_EQ(v1.z(), 9.0f);
    EXPECT_FLOAT_EQ(v1.w(), 11.0f);
}

// Test -= operator
TEST(Vec4Test, Vec4TestSubtractionAssignmentOperator) {
    vec4 v1(4.0f, 5.0f, 6.0f, 7.0f);
    vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);
    v1 -= v2;
    EXPECT_FLOAT_EQ(v1.x(), 3.0f);
    EXPECT_FLOAT_EQ(v1.y(), 3.0f);
    EXPECT_FLOAT_EQ(v1.z(), 3.0f);
    EXPECT_FLOAT_EQ(v1.w(), 3.0f);
}

// Test ostream operator
TEST(Vec4Test, Vec4TestOstreamOperator) {
    vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "vec4(1.00, 2.00, 3.00, 4.00)");
}

#endif
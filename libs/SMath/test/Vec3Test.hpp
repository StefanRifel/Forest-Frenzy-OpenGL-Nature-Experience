#ifndef VEC3TEST_HH
#define VEC3TEST_HH

#include <gtest/gtest.h>
#include "../include/vec3.hpp"

// Test default constructor
TEST(Vec3Test, Vec3TestDefaultConstructor) {
    vec3 v;
    EXPECT_FLOAT_EQ(v.x(), 0.0f);
    EXPECT_FLOAT_EQ(v.y(), 0.0f);
    EXPECT_FLOAT_EQ(v.z(), 0.0f);
}

// Test parameterized constructor
TEST(Vec3Test, Vec3TestParameterizedConstructor) {
    vec3 v {1.0f, 2.0f, 3.0f};
    EXPECT_FLOAT_EQ(v.x(), 1.0f);
    EXPECT_FLOAT_EQ(v.y(), 2.0f);
    EXPECT_FLOAT_EQ(v.z(), 3.0f);
}

// Test copy constructor
TEST(Vec3Test, Vec3TestCopyConstructor) {
    vec3 v1 {1.0f, 2.0f, 3.0f};
    vec3 v2 {v1};
    EXPECT_FLOAT_EQ(v2.x(), 1.0f);
    EXPECT_FLOAT_EQ(v2.y(), 2.0f);
    EXPECT_FLOAT_EQ(v2.z(), 3.0f);
}

// Test length method
TEST(Vec3Test, Vec3TestLength) {
    vec3 v {1.0f, 2.0f, 2.0f};
    EXPECT_FLOAT_EQ(v.length(), 3.0f);
}

// Test assignment operator
TEST(Vec3Test, Vec3TestAssignmentOperator) {
    vec3 v1 {1.0f, 2.0f, 3.0f};
    vec3 v2;
    v2 = v1;
    EXPECT_FLOAT_EQ(v2.x(), 1.0f);
    EXPECT_FLOAT_EQ(v2.y(), 2.0f);
    EXPECT_FLOAT_EQ(v2.z(), 3.0f);
}

// Test element access operator
TEST(Vec3Test, Vec3TestElementAccessOperator) {
    vec3 v {1.0f, 2.0f, 3.0f};
    EXPECT_FLOAT_EQ(v[0], 1.0f);
    EXPECT_FLOAT_EQ(v[1], 2.0f);
    EXPECT_FLOAT_EQ(v[2], 3.0f);
}

// Test equality operator
TEST(Vec3Test, Vec3TestEqualityOperator) {
    vec3 v1 {1.0f, 2.0f, 3.0f};
    vec3 v2 {1.0f, 2.0f, 3.0f};
    EXPECT_TRUE(v1 == v2);
}

// Test inequality operator
TEST(Vec3Test, Vec3TestInequalityOperator) {
    vec3 v1 {1.0f, 2.0f, 3.0f};
    vec3 v2 {4.0f, 5.0f, 6.0f};
    EXPECT_TRUE(v1 != v2);
}

// Test addition operator
TEST(Vec3Test, Vec3TestAdditionOperator) {
    vec3 v1 {1.0f, 2.0f, 3.0f};
    vec3 v2 {4.0f, 5.0f, 6.0f};
    vec3 v3 = v1 + v2;
    EXPECT_FLOAT_EQ(v3.x(), 5.0f);
    EXPECT_FLOAT_EQ(v3.y(), 7.0f);
    EXPECT_FLOAT_EQ(v3.z(), 9.0f);
}

// Test subtraction operator
TEST(Vec3Test, Vec3TestSubtractionOperator) {
    vec3 v1(4.0f, 5.0f, 6.0f);
    vec3 v2(1.0f, 2.0f, 3.0f);
    vec3 v3 = v1 - v2;
    EXPECT_FLOAT_EQ(v3.x(), 3.0f);
    EXPECT_FLOAT_EQ(v3.y(), 3.0f);
    EXPECT_FLOAT_EQ(v3.z(), 3.0f);
}

// Test scalar multiplication operator
TEST(Vec3Test, Vec3TestScalarMultiplicationOperator) {
    vec3 v(1.0f, 2.0f, 3.0f);
    vec3 v2 = v * 2.0f;
    EXPECT_FLOAT_EQ(v2.x(), 2.0f);
    EXPECT_FLOAT_EQ(v2.y(), 4.0f);
    EXPECT_FLOAT_EQ(v2.z(), 6.0f);
}

// Test += operator
TEST(Vec3Test, Vec3TestAdditionAssignmentOperator) {
    vec3 v1(1.0f, 2.0f, 3.0f);
    vec3 v2(4.0f, 5.0f, 6.0f);
    v1 += v2;
    EXPECT_FLOAT_EQ(v1.x(), 5.0f);
    EXPECT_FLOAT_EQ(v1.y(), 7.0f);
    EXPECT_FLOAT_EQ(v1.z(), 9.0f);
}

// Test -= operator
TEST(Vec3Test, Vec3TestSubtractionAssignmentOperator) {
    vec3 v1(4.0f, 5.0f, 6.0f);
    vec3 v2(1.0f, 2.0f, 3.0f);
    v1 -= v2;
    EXPECT_FLOAT_EQ(v1.x(), 3.0f);
    EXPECT_FLOAT_EQ(v1.y(), 3.0f);
    EXPECT_FLOAT_EQ(v1.z(), 3.0f);
}

// Test ostream operator
TEST(Vec3Test, Vec3TestOstreamOperator) {
    vec3 v(1.0f, 2.0f, 3.0f);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "vec3(1.00, 2.00, 3.00)");
}

#endif
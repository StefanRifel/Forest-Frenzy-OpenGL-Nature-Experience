#ifndef TRANSFORMATION_TEST_HH
#define TRANSFORMATION_TEST_HH

#include <gtest/gtest.h>
#include "../include/Transformation.hpp"

TEST(TransformationTest, TransformationTestIdentityMatrixTest) {
    mat4 identityMat;
    Transformation::identity(identityMat);

    // Check if all diagonal elements are 1 and all other elements are 0
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j) {
                EXPECT_EQ(identityMat[i][j], 1.0f);
            } else {
                EXPECT_EQ(identityMat[i][j], 0.0f);
            }
        }
    }
}

#endif
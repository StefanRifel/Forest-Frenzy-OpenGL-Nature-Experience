#ifndef TRANSFORMATION_TEST_HH
#define TRANSFORMATION_TEST_HH

#include <gtest/gtest.h>
#include "../include/Transformation.hpp"
#include <cmath>

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

TEST(TransformationTest, Translate) {
    //Einheitsmatrix und Vektor (1, 2, 3)
    mat4 in = mat4(1.0f);  // Einheitsmatrix
    vec3 v = vec3(1.0f, 2.0f, 3.0f);

    mat4 expected;
    expected[0][0] = 1.0f; expected[0][1] = 0.0f; expected[0][2] = 0.0f; expected[0][3] = 1.0f;
    expected[1][0] = 0.0f; expected[1][1] = 1.0f; expected[1][2] = 0.0f; expected[1][3] = 2.0f;
    expected[2][0] = 0.0f; expected[2][1] = 0.0f; expected[2][2] = 1.0f; expected[2][3] = 3.0f;
    expected[3][0] = 0.0f; expected[3][1] = 0.0f; expected[3][2] = 0.0f; expected[3][3] = 1.0f;

    mat4 result = Transformation::translate(in, v);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }
}

TEST(TransformationTest, Scale) {
    // Test 1: Einheitsmatrix und Vektor (2, 3, 4)
    mat4 in = mat4(1.0f);  // Einheitsmatrix
    vec3 v = vec3(2.0f, 3.0f, 4.0f);

    mat4 expected;
    expected[0][0] = 2.0f; expected[0][1] = 0.0f; expected[0][2] = 0.0f; expected[0][3] = 0.0f;
    expected[1][0] = 0.0f; expected[1][1] = 3.0f; expected[1][2] = 0.0f; expected[1][3] = 0.0f;
    expected[2][0] = 0.0f; expected[2][1] = 0.0f; expected[2][2] = 4.0f; expected[2][3] = 0.0f;
    expected[3][0] = 0.0f; expected[3][1] = 0.0f; expected[3][2] = 0.0f; expected[3][3] = 1.0f;

    mat4 result = Transformation::scale(in, v);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }

    // Test 2: Zufällige Matrix und Vektor (1, 1, 1) (sollte identisch mit der ursprünglichen Matrix sein)
    mat4 randomMatrix;
    randomMatrix[0][0] = 2.0f; randomMatrix[0][1] = 3.0f; randomMatrix[0][2] = 4.0f; randomMatrix[0][3] = 5.0f;
    randomMatrix[1][0] = 6.0f; randomMatrix[1][1] = 7.0f; randomMatrix[1][2] = 8.0f; randomMatrix[1][3] = 9.0f;
    randomMatrix[2][0] = 10.0f; randomMatrix[2][1] = 11.0f; randomMatrix[2][2] = 12.0f; randomMatrix[2][3] = 13.0f;
    randomMatrix[3][0] = 14.0f; randomMatrix[3][1] = 15.0f; randomMatrix[3][2] = 16.0f; randomMatrix[3][3] = 17.0f;

    vec3 identityVector = vec3(1.0f, 1.0f, 1.0f);
    mat4 resultIdentity = Transformation::scale(randomMatrix, identityVector);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(resultIdentity[i][j], randomMatrix[i][j], 1e-5);
        }
    }

    // Test 3: Zufällige Matrix und Vektor (0.5, 0.5, 0.5) (sollte die Matrix halbieren)
    vec3 halfVector = vec3(0.5f, 0.5f, 0.5f);
    mat4 resultHalf = Transformation::scale(randomMatrix, halfVector);

    mat4 expectedHalf;
    expectedHalf[0][0] = 1.0f; expectedHalf[0][1] = 1.5f; expectedHalf[0][2] = 2.0f; expectedHalf[0][3] = 5.0f;
    expectedHalf[1][0] = 3.0f; expectedHalf[1][1] = 3.5f; expectedHalf[1][2] = 4.0f; expectedHalf[1][3] = 9.0f;
    expectedHalf[2][0] = 5.0f; expectedHalf[2][1] = 5.5f; expectedHalf[2][2] = 6.0f; expectedHalf[2][3] = 13.0f;
    expectedHalf[3][0] = 7.0f; expectedHalf[3][1] = 7.5f; expectedHalf[3][2] = 8.0f; expectedHalf[3][3] = 17.0f;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(resultHalf[i][j], expectedHalf[i][j], 1e-5);
        }
    }
}

// Test-Funktion für Transformation::rotateZ
TEST(TransformationTest, RotateZ) {
    //Test 1: Einheitsmatrix und Winkel 90 Grad
    mat4 in = mat4(1.0f);  // Einheitsmatrix
    GLfloat angle = 90.0f;

    mat4 expected;
    GLfloat radiant = Transformation::radiant(angle);
    expected[0][0] = cos(radiant); expected[0][1] = -sin(radiant); expected[0][2] = 0.0f; expected[0][3] = 0.0f;
    expected[1][0] = sin(radiant); expected[1][1] = cos(radiant);  expected[1][2] = 0.0f; expected[1][3] = 0.0f;
    expected[2][0] = 0.0f;         expected[2][1] = 0.0f;          expected[2][2] = 1.0f; expected[2][3] = 0.0f;
    expected[3][0] = 0.0f;         expected[3][1] = 0.0f;          expected[3][2] = 0.0f; expected[3][3] = 1.0f;

    mat4 result = Transformation::rotateZ(in, angle);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }
}

// Test-Funktion für Transformation::rotateX
TEST(TransformationTest, RotateX) {
    // Test 1: Einheitsmatrix und Winkel 90 Grad
    mat4 in = mat4(1.0f);  // Einheitsmatrix
    GLfloat angle = 90.0f;

    mat4 expected;
    GLfloat radiant = Transformation::radiant(angle);
    expected[0][0] = 1.0f; expected[0][1] = 0.0f;         expected[0][2] = 0.0f;         expected[0][3] = 0.0f;
    expected[1][0] = 0.0f; expected[1][1] = cos(radiant); expected[1][2] = -sin(radiant); expected[1][3] = 0.0f;
    expected[2][0] = 0.0f; expected[2][1] = sin(radiant); expected[2][2] = cos(radiant);  expected[2][3] = 0.0f;
    expected[3][0] = 0.0f; expected[3][1] = 0.0f;         expected[3][2] = 0.0f;         expected[3][3] = 1.0f;

    mat4 result = Transformation::rotateX(in, angle);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }
}

TEST(TransformationTest, RotateY) {
    // Test 1: Einheitsmatrix und Winkel 90 Grad
    mat4 in = mat4(1.0f);  // Einheitsmatrix
    GLfloat angle = 90.0f;

    mat4 expected;
    GLfloat radiant = Transformation::radiant(angle);
    expected[0][0] = cos(radiant); expected[0][1] = 0.0f; expected[0][2] = sin(radiant); expected[0][3] = 0.0f;
    expected[1][0] = 0.0f;        expected[1][1] = 1.0f; expected[1][2] = 0.0f;         expected[1][3] = 0.0f;
    expected[2][0] = -sin(radiant); expected[2][1] = 0.0f; expected[2][2] = cos(radiant); expected[2][3] = 0.0f;
    expected[3][0] = 0.0f;        expected[3][1] = 0.0f; expected[3][2] = 0.0f;         expected[3][3] = 1.0f;

    mat4 result = Transformation::rotateY(in, angle);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }
}

// Test-Funktion für Transformation::lookAt
TEST(TransformationTest, LookAt) {
    // Test 1: Kamera schaut auf den Ursprung
    vec3 eye(0.0f, 0.0f, 1.0f);
    vec3 center(0.0f, 0.0f, 0.0f);
    vec3 up(0.0f, 1.0f, 0.0f);

    mat4 expected;
    expected[0][0] = 1.0f; expected[0][1] = 0.0f; expected[0][2] = 0.0f; expected[0][3] = 0.0f;
    expected[1][0] = 0.0f; expected[1][1] = 1.0f; expected[1][2] = 0.0f; expected[1][3] = 0.0f;
    expected[2][0] = 0.0f; expected[2][1] = 0.0f; expected[2][2] = 1.0f; expected[2][3] = -1.0f;
    expected[3][0] = -0.0f; expected[3][1] = -0.0f; expected[3][2] = 0.0f; expected[3][3] = 1.0f;

    mat4 result = Transformation::lookAt(eye, center, up);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }

    // Test 2: Kamera schaut entlang der Z-Achse nach unten
    eye = vec3(0.0f, 0.0f, 5.0f);
    center = vec3(0.0f, 0.0f, 0.0f);
    up = vec3(0.0f, 1.0f, 0.0f);

    expected[0][0] = 1.0f; expected[0][1] = 0.0f; expected[0][2] = 0.0f; expected[0][3] = 0.0f;
    expected[1][0] = 0.0f; expected[1][1] = 1.0f; expected[1][2] = 0.0f; expected[1][3] = 0.0f;
    expected[2][0] = 0.0f; expected[2][1] = 0.0f; expected[2][2] = 1.0f; expected[2][3] = -5.0f;
    expected[3][0] = -0.0f; expected[3][1] = -0.0f; expected[3][2] = 0.0f; expected[3][3] = 1.0f;

    result = Transformation::lookAt(eye, center, up);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }

    // Test 3: Kamera schaut von (3,2,3) auf den Ursprung
    eye = vec3(3.0f, 2.0f, 3.0f);
    center = vec3(0.0f, 0.0f, 0.0f);
    up = vec3(0.0f, 1.0f, 0.0f);

    expected[0][0] = 0.707107f; expected[0][1] = -0.301511f; expected[0][2] = 0.639602f; expected[0][3] = 0.0f;
    expected[1][0] = 0.0f; expected[1][1] = 0.904534f; expected[1][2] = 0.426401f; expected[1][3] = 0.0f;
    expected[2][0] = -0.707107f; expected[2][1] = -0.301511f; expected[2][2] = 0.639602f; expected[2][3] = -4.69042f;
    expected[3][0] = -0.0f; expected[3][1] = -0.0f; expected[3][2] = 0.0f; expected[3][3] = 1.0f;

    result = Transformation::lookAt(eye, center, up);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_FLOAT_EQ(std::trunc(result[i][j] * std::pow(10.0f, 3) / std::pow(10.0f, 3)), std::trunc(expected[i][j] * std::pow(10.0f, 3) / std::pow(10.0f, 3))) << "Mismatch at (" << i << ", " << j << ")";
        }
    }
}

// Test-Funktion für Transformation::perspective
TEST(TransformationTest, Perspective) {
    // Test 1: Standardperspektive
    float fov = 90.0f;
    float aspect = 1.0f;
    float near = 0.1f;
    float far = 100.0f;

    mat4 expected;
    float fovRad = Transformation::radiant(fov) / 2.0f;
    expected[0][0] = 1.0f / (aspect * tan(fovRad));
    expected[1][1] = 1.0f / tan(fovRad);
    expected[2][2] = -((far + near) / (far - near));
    expected[2][3] = -((2.0f * far * near) / (far - near));
    expected[3][2] = -1.0f;
    expected[3][3] = 0.0f;

    mat4 result = Transformation::perspective(fov, aspect, near, far);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }

    // Test 2: Perspektive mit anderem Seitenverhältnis
    fov = 60.0f;
    aspect = 16.0f / 9.0f;
    near = 0.1f;
    far = 1000.0f;

    expected[0][0] = 1.0f / (aspect * tan(Transformation::radiant(fov) / 2.0f));
    expected[1][1] = 1.0f / tan(Transformation::radiant(fov) / 2.0f);
    expected[2][2] = -((far + near) / (far - near));
    expected[2][3] = -((2.0f * far * near) / (far - near));
    expected[3][2] = -1.0f;
    expected[3][3] = 0.0f;

    result = Transformation::perspective(fov, aspect, near, far);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }
}

// Test-Funktion für Transformation::ortho
TEST(TransformationTest, Ortho) {
    // Test 1: Standard Orthografie mit symmetrischen Grenzen
    float left = -1.0f;
    float right = 1.0f;
    float bottom = -1.0f;
    float top = 1.0f;
    float nearPlane = -1.0f;
    float farPlane = 1.0f;

    mat4 expected(1.0f);
    expected[0][0] = 1.0f;
    expected[1][1] = 1.0f;
    expected[2][2] = -1.0f;
    expected[3][0] = 0.0f;
    expected[3][1] = 0.0f;
    expected[3][2] = 0.0f;

    mat4 result = Transformation::ortho(left, right, bottom, top, nearPlane, farPlane);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }

    // Test 2: Orthografie mit unterschiedlichen Grenzen
    left = 0.0f;
    right = 2.0f;
    bottom = 0.0f;
    top = 2.0f;
    nearPlane = 1.0f;
    farPlane = 3.0f;

    expected[0][0] = 1.0f;
    expected[1][1] = 1.0f;
    expected[2][2] = -1.0f;
    expected[3][0] = -1.0f;
    expected[3][1] = -1.0f;
    expected[3][2] = -2.0f;

    result = Transformation::ortho(left, right, bottom, top, nearPlane, farPlane);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_NEAR(result[i][j], expected[i][j], 1e-5);
        }
    }
}

#endif
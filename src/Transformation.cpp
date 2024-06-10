#include "../include/Transformation.hpp"

/**
 * @brief Sets the given matrix to the identity matrix.
 *
 * @param out The matrix to be set to identity.
 */
void Transformation::identity(mat4& out) {
    for (int x = 0; x < MAT4_ROW_SIZE; x++) {
        for (int y = 0; y < MAT4_COLUMN_SIZE; y++) {
            x == y ? out[x][y] = 1.0f : out[x][y] = 0.0f;
        }
    }
}

/**
 * @brief Translates the given matrix by the vector v.
 *
 * @param in The input matrix.
 * @param v The translation vector.
 * @return The translated matrix.
 *
 * \verbatim
 * Translation Matrix:
 * | 1  0  0  Tx |
 * | 0  1  0  Ty |
 * | 0  0  1  Tz |
 * | 0  0  0  1  |
 * \endverbatim
 */
mat4 Transformation::translate(mat4& in, vec3& v) {
    mat4 translationMatrix {1.0f};
    translationMatrix[0][3] = v.x();  
    translationMatrix[1][3] = v.y();
    translationMatrix[2][3] = v.z();

    return in * translationMatrix;
}

/**
 * @brief Scales the given matrix by the vector v.
 *
 * @param in The input matrix.
 * @param v The scaling vector.
 * @return The scaled matrix.
 *
 * \verbatim
 * Scaling Matrix:
 * | Sx  0   0   0 |
 * |  0  Sy  0   0 |
 * |  0   0  Sz  0 |
 * |  0   0   0  1 |
 * \endverbatim
 */
mat4 Transformation::scale(mat4& in, vec3& v) {
    mat4 scaleMatrix {1.0f};
    scaleMatrix[0][0] = v.x();  
    scaleMatrix[1][1] = v.y();
    scaleMatrix[2][2] = v.z();

    return in * scaleMatrix;
}

/**
 * @brief Rotates the given matrix around the Z axis.
 *
 * @param in The input matrix.
 * @param angle The rotation angle in degrees.
 * @return The rotated matrix.
 *
 * \verbatim
 * Rotation Z Matrix:
 * | cos -sin  0  0 |
 * | sin  cos  0  0 |
 * |  0    0   1  0 |
 * |  0    0   0  1 |
 * \endverbatim
 */
mat4 Transformation::rotateZ(mat4& in, GLfloat angle) {
    mat4 rotateZMatrix {1.0f};
    GLfloat radiant = Transformation::radiant(angle);
    rotateZMatrix[0][0] = (GLfloat)cos(radiant);
    rotateZMatrix[0][1] = (GLfloat)-sin(radiant);
    rotateZMatrix[1][0] = (GLfloat)sin(radiant);
    rotateZMatrix[1][1] = (GLfloat)cos(radiant);

    return in * rotateZMatrix;
}

/**
 * @brief Rotates the given matrix around the X axis.
 *
 * @param in The input matrix.
 * @param angle The rotation angle in degrees.
 * @return The rotated matrix.
 *
 * \verbatim
 * Rotation X Matrix:
 * |  1   0    0   0 |
 * |  0  cos -sin  0 |
 * |  0  sin  cos  0 |
 * |  0   0    0   1 |
 * \endverbatim
 */
mat4 Transformation::rotateX(mat4& in, GLfloat angle) {
    mat4 rotateXMatrix {1.0f};
    GLfloat radiant = Transformation::radiant(angle);
    rotateXMatrix[1][1] = (GLfloat)cos(radiant);
    rotateXMatrix[1][2] = (GLfloat)-sin(radiant);
    rotateXMatrix[2][1] = (GLfloat)sin(radiant);
    rotateXMatrix[2][2] = (GLfloat)cos(radiant);

    return in * rotateXMatrix;
}

/**
 * @brief Rotates the given matrix around the Y axis.
 *
 * @param in The input matrix.
 * @param angle The rotation angle in degrees.
 * @return The rotated matrix.
 *
 * \verbatim
 * Rotation Y Matrix:
 * | cos   0  sin  0 |
 * |  0    1   0   0 |
 * |-sin   0  cos  0 |
 * |  0    0   0   1 |
 * \endverbatim
 */
mat4 Transformation::rotateY(mat4& in, GLfloat angle) {
    mat4 rotateYMatrix {1.0f};
    GLfloat radiant = Transformation::radiant(angle);
    rotateYMatrix[0][0] = (GLfloat)cos(radiant);
    rotateYMatrix[0][2] = (GLfloat)sin(radiant);
    rotateYMatrix[2][0] = (GLfloat)-sin(radiant);
    rotateYMatrix[2][2] = (GLfloat)cos(radiant);

    return in * rotateYMatrix;
}

/**
 * @brief Normalizes the given vector.
 *
 * @param v The vector to normalize.
 * @return The normalized vector.
 */
vec3 Transformation::normalize(const vec3& v) {
    return v * (1.0f / v.length());
}

/**
 * @brief Computes the cross product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The cross product vector.
 */
vec3 Transformation::cross(vec3& a, vec3& b) {
    vec3 result {};
    result[0] = (a[1] * b[2]) - (a[2] * b[1]);
    result[1] = (a[2] * b[0]) - (a[0] * b[2]);
    result[2] = (a[0] * b[1]) - (a[1] * b[0]);
    return result;
}

/**
 * @brief Computes the dot product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product.
 */
float Transformation::dot(vec3& a, vec3& b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

/**
 * @brief Creates a look-at view matrix.
 *
 * @param eye The position of the camera.
 * @param center The point the camera is looking at.
 * @param up The up direction vector.
 * @return The view matrix.
 *
 * \verbatim
 * View Matrix:
 * |  u'x  u'y  u'z  tx  |
 * |  v'x  v'y  v'z  ty  |
 * |  n'x  n'y  n'z  tz  |
 * |    0    0    0   1  |
 * \endverbatim
 */
mat4 Transformation::lookAt(vec3& eye, vec3& center, vec3& up, vec3& right, vec3& worldUp) {
    // n
    vec3 cameraDirection {Transformation::normalize(eye - center)};
    // u
    vec3 cameraRight {Transformation::normalize(Transformation::cross(up, cameraDirection))};
    right = cameraRight;
    // v
    vec3 cameraUp {Transformation::cross(cameraDirection, cameraRight)};
    worldUp = cameraUp;

    mat4 view {1.0f};
    // set right vector
    view[0][0] = cameraRight[0];
    view[0][1] = cameraRight[1];
    view[0][2] = cameraRight[2];

    // set up vector
    view[1][0] = cameraUp[0];
    view[1][1] = cameraUp[1];
    view[1][2] = cameraUp[2];

    // set direction vector
    view[2][0] = cameraDirection[0];
    view[2][1] = cameraDirection[1];
    view[2][2] = cameraDirection[2];

    // set translation vector
    view[0][3] = -Transformation::dot(cameraRight, eye);
    view[1][3] = -Transformation::dot(cameraUp, eye);
    view[2][3] = -Transformation::dot(cameraDirection, eye);

    return view;
}

/**
 * @brief Creates a perspective projection matrix.
 *
 * @param fov The field of view in degrees.
 * @param aspect The aspect ratio.
 * @param near The near clipping plane.
 * @param far The far clipping plane.
 * @return The projection matrix.
 */
mat4 Transformation::perspective(float fov, float aspect, float near, float far) {
    mat4 projection {1.0f};

    projection[0][0] = 1.0f / (aspect * tan(Transformation::radiant(fov) / 2.0f));
    projection[1][1] = 1.0f / tan(Transformation::radiant(fov) / 2.0f);
    projection[2][2] = -((far + near) / (far - near));
    projection[2][3] = -((2.0f * far * near) / (far - near));
    projection[3][2] = -1.0f;
    projection[3][3] = 0.0f;

    return projection;
}

GLfloat Transformation::radiant(GLfloat angle) {
    return (GLfloat)(angle * M_PI /180);
}
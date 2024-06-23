#ifndef TRANSFORMATION_HH
#define TRANSFORMATION_HH

#include <GL/glew.h>

#include <string>
#include <cmath>

#include <iostream>

#include "../libs/SMath/include/mat4.hpp"
#include "../libs/SMath/include/vec3.hpp"

/**
 * @class Transformation
 * @brief A collection of static methods for performing various transformations on 3D matrices and vectors.
 *
 * This class provides methods to perform common 3D transformations such as translation,
 * scaling, and rotation. It also includes utility functions for setting up view and
 * projection matrices, as well as vector operations.
 *
 * Transformations should be applied in the following order for optimal results:
 * 1. Scaling
 * 2. Rotation
 * 3. Translation
 * This order prevents transformations from negatively affecting each other.
 *
 * Example:
 * \verbatim
 *       +------------+             +------------+            +-------------+
 *       |            |   Scale     |            |  Rotate    |             | Translate
 *       |            |  ------>    |            |  ------>   |             | -------->
 *       |            |             |            |            |             |
 *       +------------+             +------------+            +-------------+
 * \endverbatim
 */
class Transformation {
private:

public:
    static void identity(mat4& matrix);
    static mat4 translate(mat4& in, vec3& v);
    static mat4 scale(mat4& in, vec3& v);

    static mat4 rotateZ(mat4& in, GLfloat angle);
    static mat4 rotateX(mat4& in, GLfloat angle);
    static mat4 rotateY(mat4& in, GLfloat angle);

    static mat4 lookAt(vec3& eye, vec3& center, vec3& up);
    static mat4 perspective(float fov, float aspect, float near, float far);
    static mat4 ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    static vec3 normalize(const vec3& v);
    static vec3 cross(vec3& a, vec3& b);
    static float dot(vec3& a, vec3& b);

    static GLfloat radiant(GLfloat angle);

    static void removeTranslation(mat4& mat);
};

#endif
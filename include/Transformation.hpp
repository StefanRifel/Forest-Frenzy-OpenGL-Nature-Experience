#ifndef TRANSFORMATION_HH
#define TRANSFORMATION_HH

#include <GL/glew.h>
#include <string>
#include "../libs/SMath/include/mat4.hpp"
#include "../libs/SMath/include/vec3.hpp"

class Transformation {
private:

public:
    // It is advised to first do scaling operations, then rotations and lastly translations
    // when combining matrices otherwise they may (negatively) affect each other.
    static void identity(mat4& matrix);
    static mat4 translate(mat4& in, vec3& v);
    static mat4 scale(mat4& in, vec3& v);
    // Rotate in this order: Rx , Ry , Rz
    // to prevent Gimbal lock
    static mat4 rotateZ(mat4& in, GLuint angle);
    static mat4 rotateX(mat4& in, GLuint angle);
    static mat4 rotateY(mat4& in, GLuint angle);

    static mat4 lookAt(vec3 eye, vec3 center, vec3 up);
    static mat4 perspective(float fov, float aspect, float near, float far);
    static vec3 normalize(const vec3& v);
    static vec3 cross(vec3& a, vec3& b);
    static float dot(vec3& a, vec3& b);

    static vec3 calcPointOnCircle(int angle, float radius);
    static float radiant(float angle);
    
};

#endif
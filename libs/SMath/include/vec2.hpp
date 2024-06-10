#ifndef VEC2_HH
#define VEC2_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>
#include <cmath>

const GLuint VEC2_SIZE = 2;

class vec2 {

private:
    GLfloat vector[VEC2_SIZE];

public:
    vec2();
    vec2(GLfloat x, GLfloat y);
    vec2(const vec2& v);

    ~vec2();

    GLfloat& x();
    GLfloat& y();

    friend std::ostream& operator<< (std::ostream& out, const vec2& v);

    vec2& operator= (const vec2& v);
    float& operator[] (GLuint index);
    friend bool operator== (const vec2& v1, const vec2& v2);
    friend bool operator!= (const vec2& v1, const vec2& v2);

    vec2 operator+ (const vec2& v) const;
    vec2 operator+= (const vec2& v);

    vec2 operator- (const vec2& v) const;
    vec2 operator-= (const vec2& v);

    vec2 operator* (const GLfloat a) const;
};

#endif
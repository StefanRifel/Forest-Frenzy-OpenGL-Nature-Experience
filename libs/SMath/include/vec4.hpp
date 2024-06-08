#ifndef VEC4_HH
#define VEC4_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>
#include <cmath>

const unsigned int VEC4_SIZE = 4;

class vec4
{
private:
    GLfloat vector[VEC4_SIZE];
public:
    vec4();
    vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    vec4(const vec4& v);

    ~vec4();

    GLfloat& x();
    GLfloat& y();
    GLfloat& z();
    GLfloat& w();

    const GLfloat& r() const;
    const GLfloat& g() const;
    const GLfloat& b() const;
    const GLfloat& a() const;

    friend std::ostream& operator<< (std::ostream& out, const vec4& v);

    vec4& operator= (const vec4& v);
    float& operator[] (GLuint index);
    friend bool operator== (const vec4& v1, const vec4& v2);
    friend bool operator!= (const vec4& v1, const vec4& v2);

    vec4 operator+ (const vec4& v) const;
    vec4 operator+= (const vec4& v);

    vec4 operator- (const vec4& v) const;
    vec4 operator-= (const vec4& v);

    vec4 operator* (const GLfloat a) const;
};

#endif
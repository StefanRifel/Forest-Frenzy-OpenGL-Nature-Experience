#ifndef VEC3_HH
#define VEC3_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>
#include <cmath>

const GLuint VEC3_SIZE = 3;

class vec3 {
    
private:
    GLfloat* vector;

public:
    vec3();
    vec3(GLfloat x, GLfloat y, GLfloat z);
    vec3(const vec3& v);

    ~vec3();

    GLfloat& x();
    GLfloat& y();
    GLfloat& z();
    GLfloat& r() const;
    GLfloat& g() const;
    GLfloat& b() const;

    GLfloat length() const;

    friend std::ostream& operator<< (std::ostream& out, const vec3& v);

    vec3& operator= (const vec3& v);
    float& operator[] (GLuint index);
    friend bool operator== (const vec3& v1, const vec3& v2);
    friend bool operator!= (const vec3& v1, const vec3& v2);

    vec3 operator+ (const vec3& v) const;
    vec3 operator+= (const vec3& v);

    vec3 operator- (const vec3& v) const;
    vec3 operator-= (const vec3& v);

    vec3 operator* (const GLfloat a) const;
};

#endif
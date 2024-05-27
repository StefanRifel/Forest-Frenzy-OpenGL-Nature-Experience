#ifndef VEC3_HH
#define VEC3_HH

const int VEC_N = 3;

#include <iostream>
#include <array>
#include <cmath>

class vec3
{
private:
    std::array<float, VEC_N> vector;
public:
    vec3();
    vec3(float x, float y, float z);
    vec3(const vec3& v);
    ~vec3();

    float& x();
    float& y();
    float& z();
    const float r() const;
    const float g() const;
    const float b() const;

    float length() const;

    friend std::ostream& operator<< (std::ostream& out, const vec3& v);

    vec3& operator= (const vec3& v);
    float& operator[] (int index);

    vec3 operator+ (const vec3& v) const;
    vec3 operator+= (const vec3& v);

    vec3 operator- (const vec3& v) const;
    vec3 operator-= (const vec3& v);

    vec3 operator* (const float a) const;
};

#endif
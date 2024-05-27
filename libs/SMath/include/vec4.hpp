#ifndef VEC4_HH
#define VEC4_HH

const int N = 4;

#include <iostream>
#include <array>

class vec4
{
private:
    std::array<float, 4> vector;
public:
    vec4();
    vec4(float x, float y, float z, float w);
    vec4(const vec4& v);
    ~vec4();

    float x();
    float y();
    float z();
    float w();

    float r();
    float g();
    float b();
    float a();

    friend std::ostream& operator<< (std::ostream& out, const vec4& v);

    vec4& operator= (const vec4& v);
    float& operator[] (int index);

    vec4 operator+ (const vec4& v) const;
    vec4 operator+= (const vec4& v);

    vec4 operator- (const vec4& v) const;
    vec4 operator-= (const vec4& v);

    vec4 operator* (const float a) const;
};

#endif
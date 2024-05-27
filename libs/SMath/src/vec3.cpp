#include "../include/vec3.hpp"

vec3::vec3() : vector {0, 0, 0} {

}

vec3::vec3(float x, float y, float z) : vector {x, y, z} {

}

vec3::vec3(const vec3& v) {
    *this = v;
}

vec3::~vec3() {

}

float& vec3::x() {
    return vector[0];
}

float& vec3::y() {
    return vector[1];
}

float& vec3::z() {
    return vector[2];
}

const float vec3::r() const {
    return vector[0];
}

const float vec3::g() const {
    return vector[1];
}

const float vec3::b() const {
    return vector[2];
}

float vec3::length() const {
    return sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}

std::ostream& operator << (std::ostream& out, const vec3& v) {
    out << "(" << v.vector[0]; 
    for (int i = 1; i < VEC_N; i++) {
        out << ", " << v.vector[i]; 
    }
    out << ")";
    return out;
}

vec3& vec3::operator= (const vec3& v) {
    if(this == &v) {
        return *this;
    }
    for(int i = 0; i < VEC_N; i++) {
        vector[i] = v.vector[i]; 
    }
    return *this;
}

vec3 vec3::operator+ (const vec3& v) const {
    vec3 result {*this};
    result += v;
    return result;
}

vec3 vec3::operator+= (const vec3& v) {
    for(int i = 0; i < VEC_N; i++) {
        vector[i] += v.vector[i]; 
    }
    return *this;
}

vec3 vec3::operator- (const vec3& v) const {
    vec3 result {*this};
    result -= v;
    return result;
}

vec3 vec3::operator-= (const vec3& v) {
    for(int i = 0; i < VEC_N; i++) {
        vector[i] -= v.vector[i]; 
    }
    return *this;
}

vec3 vec3::operator* (const float a) const {
    vec3 result {};
    for(int i = 0; i < VEC_N; i++) {
        result.vector[i] = this->vector[i] * a;
    }
    return result;
}

float& vec3::operator [] (int index) {
    if (index < 0 || index >= VEC_N) {
        throw std::__throw_invalid_argument;
    }
    return vector[index];
}
#include "../include/vec4.hpp"

vec4::vec4() : vector {0, 0, 0} {

}

vec4::vec4(float x, float y, float z, float w) : vector {x, y, z, w} {

}

vec4::vec4(const vec4& v) {
    *this = v;
}

vec4::~vec4() {

}

float vec4::x() {
    return vector[0];
}

float vec4::y() {
    return vector[1];
}

float vec4::z() {
    return vector[2];
}

float vec4::w() {
    return vector[3];
}

float vec4::r() {
    return vector[0];
}

float vec4::g() {
    return vector[1];
}

float vec4::b() {
    return vector[2];
}

float vec4::a() {
    return vector[3];
}

std::ostream& operator << (std::ostream& out, const vec4& v) {
    out << "(" << v.vector[0]; 
    for (int i = 1; i < N; i++) {
        out << ", " << v.vector[i]; 
    }
    out << ")";
    return out;
}

vec4& vec4::operator= (const vec4& v) {
    if(this == &v) return *this;

    for(int i = 0; i < N; i++) {
        vector[i] = v.vector[i]; 
    }
    
    return *this;
}

vec4 vec4::operator+ (const vec4& v) const {
    vec4 result {*this};
    result += v;
    return result;
}

vec4 vec4::operator+= (const vec4& v) {
    for(int i = 0; i < N; i++) {
        vector[i] += v.vector[i]; 
    }
    return *this;
}

vec4 vec4::operator- (const vec4& v) const {
    vec4 result {*this};
    result -= v;
    return result;
}

vec4 vec4::operator-= (const vec4& v) {
    for(int i = 0; i < N; i++) {
        vector[i] -= v.vector[i]; 
    }
    return *this;
}

vec4 vec4::operator* (const float a) const {
    vec4 result {};
    for(int i = 0; i < N; i++) {
        result.vector[i] = this->vector[i] * a;
    }
    return result;
}

float& vec4::operator [] (int index) {
    if (index < 0 || index >= N) {
        throw std::__throw_invalid_argument;
    }
    return vector[index];
}
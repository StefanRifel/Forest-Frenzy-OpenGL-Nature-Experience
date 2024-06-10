#include "../include/vec2.hpp"

vec2::vec2() {
    for (int i = 0; i < VEC2_SIZE; i++) {
        vector[i] = 0.0f;
    }
}

vec2::vec2(GLfloat x, GLfloat y) {
    vector[0] = x;
    vector[1] = y;
}

vec2::vec2(const vec2& v) {
    *this = v;
}

vec2::~vec2() {
}

GLfloat& vec2::x() {
    return vector[0];
}

GLfloat& vec2::y() {
    return vector[1];
}

std::ostream& operator << (std::ostream& out, const vec2& v) {
    out << std::fixed << std::setprecision(2);
    out << "vec3(" << v.vector[0];
    for (int i = 1; i < VEC2_SIZE; i++) {
        out << ", " << v.vector[i];
    }
    out << ")";
    return out;
}

vec2& vec2::operator= (const vec2& v) {
    if(this == &v) {
        return *this;
    }

    for(int i = 0; i < VEC2_SIZE; i++) {
        vector[i] = v.vector[i];
    }

    return *this;
}

bool operator== (const vec2& v1, const vec2& v2) {
    for(int i = 0; i < VEC2_SIZE; i++) {
        if(v1.vector[i] != v2.vector[i]){
            return false;
        }
    }
    return true;
}

bool operator!= (const vec2& v1, const vec2& v2) {
    for(int i = 0; i < VEC2_SIZE; i++) {
        if(v1.vector[i] != v2.vector[i]){
            return true;
        }
    }
    return false;
}

vec2 vec2::operator+ (const vec2& v) const {
    vec2 result {*this};
    result += v;
    return result;
}

vec2 vec2::operator+= (const vec2& v) {
    for(int i = 0; i < VEC2_SIZE; i++) {
        vector[i] += v.vector[i];
    }
    return *this;
}

vec2 vec2::operator- (const vec2& v) const {
    vec2 result {*this};
    result -= v;
    return result;
}

vec2 vec2::operator-= (const vec2& v) {
    for(int i = 0; i < VEC2_SIZE; i++) {
        vector[i] -= v.vector[i];
    }
    return *this;
}

vec2 vec2::operator* (const GLfloat a) const {
    vec2 result {};
    for(int i = 0; i < VEC2_SIZE; i++) {
        result.vector[i] = this->vector[i] * a;
    }
    return result;
}

float& vec2::operator [] (GLuint index) {
    if (index < 0 || index >= VEC2_SIZE) {
        throw std::__throw_invalid_argument;
    }
    return vector[index];
}
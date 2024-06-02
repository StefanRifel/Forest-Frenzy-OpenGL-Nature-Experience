#include "../include/vec3.hpp"

vec3::vec3() {
    vector = (GLfloat*)malloc(VEC3_SIZE * sizeof(GLfloat));
    for (int i = 0; i < VEC3_SIZE; i++) {
        vector[i] = 0.0f; 
    }
}

vec3::vec3(GLfloat x, GLfloat y, GLfloat z) {
    vector = (GLfloat*)malloc(VEC3_SIZE * sizeof(GLfloat));
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
}

vec3::vec3(const vec3& v) {
    vector = nullptr;
    *this = v;
}

vec3::~vec3() {
    free(vector);
}

GLfloat& vec3::x() {
    return vector[0];
}

GLfloat& vec3::y() {
    return vector[1];
}

GLfloat& vec3::z() {
    return vector[2];
}

GLfloat& vec3::r() {
    return vector[0];
}

GLfloat& vec3::g() {
    return vector[1];
}

GLfloat& vec3::b() {
    return vector[2];
}

GLfloat vec3::length() const {
    return sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}

std::ostream& operator << (std::ostream& out, const vec3& v) {
    out << std::fixed << std::setprecision(2);
    out << "vec3(" << v.vector[0]; 
    for (int i = 1; i < VEC3_SIZE; i++) {
        out << ", " << std::setw(2) << v.vector[i]; 
    }
    out << ")";
    return out;
}

vec3& vec3::operator= (const vec3& v) {
    if(this == &v) {
        return *this;
    }

    free(vector);
    vector = (GLfloat*)malloc(VEC3_SIZE * sizeof(GLfloat));

    for(int i = 0; i < VEC3_SIZE; i++) {
        vector[i] = v.vector[i]; 
    }

    return *this;
}

bool operator== (const vec3& v1, const vec3& v2) {
    for(int i = 0; i < VEC3_SIZE; i++) {
        if(v1.vector[i] != v2.vector[i]){
            return false;
        }
    }
    return true;
}

bool operator!= (const vec3& v1, const vec3& v2) {
    for(int i = 0; i < VEC3_SIZE; i++) {
        if(v1.vector[i] != v2.vector[i]){
            return true;
        }
    }
    return false;
}

vec3 vec3::operator+ (const vec3& v) const {
    vec3 result {*this};
    result += v;
    return result;
}

vec3 vec3::operator+= (const vec3& v) {
    for(int i = 0; i < VEC3_SIZE; i++) {
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
    for(int i = 0; i < VEC3_SIZE; i++) {
        vector[i] -= v.vector[i]; 
    }
    return *this;
}

vec3 vec3::operator* (const GLfloat a) const {
    vec3 result {};
    for(int i = 0; i < VEC3_SIZE; i++) {
        result.vector[i] = this->vector[i] * a;
    }
    return result;
}

float& vec3::operator [] (GLuint index) {
    if (index < 0 || index >= VEC3_SIZE) {
        throw std::__throw_invalid_argument;
    }
    return vector[index];
}
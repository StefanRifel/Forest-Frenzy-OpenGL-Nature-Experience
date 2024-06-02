#include "../include/vec4.hpp"

vec4::vec4() {
    vector = (GLfloat*)malloc(VEC4_SIZE * sizeof(GLfloat));
    vector[0] = 0.0f;
    vector[1] = 0.0f;
    vector[2] = 0.0f;
    vector[3] = 0.0f;
}

vec4::vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    vector = (GLfloat*)malloc(VEC4_SIZE * sizeof(GLfloat));
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    vector[3] = w;
}

vec4::vec4(const vec4& v) {
    vector = nullptr;
    *this = v;
}

vec4::~vec4() {

}

GLfloat& vec4::x() {
    return vector[0];
}

GLfloat& vec4::y() {
    return vector[1];
}

GLfloat& vec4::z() {
    return vector[2];
}

GLfloat& vec4::w() {
    return vector[3];
}

GLfloat& vec4::r() {
    return vector[0];
}

GLfloat& vec4::g() {
    return vector[1];
}

GLfloat& vec4::b() {
    return vector[2];
}

GLfloat& vec4::a() {
    return vector[3];
}

std::ostream& operator << (std::ostream& out, const vec4& v) {
    out << std::fixed << std::setprecision(2);
    out << "vec4(" << v.vector[0]; 
    for (int i = 1; i < VEC4_SIZE; i++) {
        out << ", " << v.vector[i]; 
    }
    out << ")";
    return out;
}

vec4& vec4::operator= (const vec4& v) {
    if(this == &v) {
        return *this;
    }

    free(vector);
    vector = (GLfloat*)malloc(VEC4_SIZE * sizeof(GLfloat));

    for(int i = 0; i < VEC4_SIZE; i++) {
        vector[i] = v.vector[i]; 
    }
    
    return *this;
}

bool operator== (const vec4& v1, const vec4& v2) {
    for(int i = 0; i < VEC4_SIZE; i++) {
        if(v1.vector[i] != v2.vector[i]){
            return false;
        }
    }
    return true;
}

bool operator!= (const vec4& v1, const vec4& v2) {
    for(int i = 0; i < VEC4_SIZE; i++) {
        if(v1.vector[i] != v2.vector[i]){
            return true;
        }
    }
    return false;
}

vec4 vec4::operator+ (const vec4& v) const {
    vec4 result {*this};
    result += v;
    return result;
}

vec4 vec4::operator+= (const vec4& v) {
    for(int i = 0; i < VEC4_SIZE; i++) {
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
    for(int i = 0; i < VEC4_SIZE; i++) {
        vector[i] -= v.vector[i]; 
    }
    return *this;
}

vec4 vec4::operator* (const GLfloat a) const {
    vec4 result {};
    for(int i = 0; i < VEC4_SIZE; i++) {
        result.vector[i] = this->vector[i] * a;
    }
    return result;
}

float& vec4::operator [] (GLuint index) {
    if (index < 0 || index >= VEC4_SIZE) {
        throw std::__throw_invalid_argument;
    }
    return vector[index];
}
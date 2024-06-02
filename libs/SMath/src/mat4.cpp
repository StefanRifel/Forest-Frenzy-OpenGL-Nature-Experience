#include "../include/mat4.hpp"

mat4::mat4() {
    for (int x = 0; x < MAT_N; x++) {
        for (int y = 0; y < MAT_N; y++) {
            matrix[x][y] = 0.0f; 
        }
    }
}

mat4::mat4(float identity) {
    if(identity != 1.0f) {
        identity == 1.0f;
    }

    for (int x = 0; x < MAT_N; x++) {
        for (int y = 0; y < MAT_N; y++) {
            x == y ? matrix[x][y] = identity : matrix[x][y] = 0.0f;
        }
    }
}

mat4::mat4(const mat4& mat) {
    *this = mat;
}

mat4::~mat4() {

}

const float* mat4::valuePtr() const {
    static float matPtr[16] = {0.0f};
    int i = 0;
    for (int x = 0; x < MAT_N; x++) {
        for (int y = 0; y < MAT_N; y++) {
            matPtr[i] = matrix[y][x];
            i++;
        }
    }
    return matPtr;
}

std::ostream& operator<< (std::ostream& out, const mat4& mat) {
    for (int x = 0; x < MAT_N; x++) {
        out << "|";
        for (int y = 0; y < MAT_N; y++) {
            out << std::setw(12) << std::right << mat.matrix[x][y]; 
        }
        out << " |\n";
    }
    return out;
}

mat4& mat4::operator= (const mat4& mat) {
    if(this == &mat) return *this;

    for (int x = 0; x < MAT_N; x++) {
        for (int y = 0; y < MAT_N; y++) {
            matrix[x][y] = mat.matrix[x][y]; 
        }
    }

    return *this;
}

std::array<float, MAT_N>& mat4::operator[] (int index) {
    if (index < 0 || index >= MAT_N) {
        throw std::__throw_invalid_argument;
    }
    return matrix[index];
}

mat4 mat4::operator* (const float a) const {
    mat4 result {};
    for (size_t i = 0; i < MAT_N; i++) {
        for (size_t j = 0; j < MAT_N; j++) {
            result.matrix[i][j] += a * matrix[i][j];
        }
    }
    return result;
}

mat4 mat4::operator* (const mat4& mat) const {
    mat4 result {};
    for (size_t i = 0; i < MAT_N; i++) {
        for (size_t j = 0; j < MAT_N; j++) {
            for (size_t k = 0; k < MAT_N; k++) {
                result.matrix[i][j] += matrix[i][k] * mat.matrix[k][j];
            }
        }
    }
    return result;
}
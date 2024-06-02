#include "../include/mat4.hpp"

mat4::mat4() {
    matrix = (GLfloat*)malloc(MAT4_SIZE * sizeof(GLfloat));

    for (int i = 0; i < MAT4_SIZE; i++) {
        matrix[i] = 0.0f; 
    }
}

mat4::mat4(GLfloat identity) {
    matrix = (GLfloat*)malloc(MAT4_SIZE * sizeof(GLfloat));
    if(identity != 1.0f) {
        throw std::__throw_invalid_argument;
    }

    for (int i = 0; i < MAT4_SIZE; i++) {
        (i % 5) == 0 ? matrix[i] = identity : matrix[i] = 0.0f;
    }
}

mat4::mat4(const mat4& mat) {
    matrix = nullptr;
    *this = mat;
}

mat4::mat4(const GLfloat* m) {
    matrix = (GLfloat*)malloc(MAT4_SIZE * sizeof(GLfloat));
    for (int i = 0; i < MAT4_SIZE; i++) {
        matrix[i] = m[i]; 
    }
}

mat4::~mat4() {
    free(matrix);
}

std::ostream& operator<< (std::ostream& out, const mat4& mat) {
    out << "mat4(\n";
    out << "        X         Y         Z         W\n";
    for (int i = 0; i < MAT4_COLUMN_SIZE; ++i) {
        out << "|   ";
        for (int j = 0; j < MAT4_ROW_SIZE; ++j) {
            out << std::setw(8) << std::setprecision(2) << std::fixed << mat.matrix[i * 4 + j];
            if (j != 3) {
                out << "  ";
            }
        }
        out << "   |\n";
    }
    out << ")\n";
    return out;
}


mat4& mat4::operator= (const mat4& mat) {
    if(this == &mat) return *this;

    free(matrix);
    matrix = (GLfloat*)malloc(MAT4_SIZE * sizeof(GLfloat));

    for (int i = 0; i < MAT4_SIZE; i++) {
        matrix[i] = mat.matrix[i]; 
    }

    return *this;
}

GLfloat& mat4::operator[] (int index) {
    if (index < 0 || index >= MAT4_SIZE) {
        throw std::__throw_invalid_argument;
    }
    return matrix[index];
}

mat4 mat4::operator* (const float a) const {
    mat4 result {};
    for (size_t i = 0; i < MAT4_SIZE; i++) {
        result.matrix[i] += a * matrix[i];
    }
    return result;
}

mat4 mat4::operator* (const mat4& mat) const {
    mat4 result;
    for (int col = 0; col < MAT4_COLUMN_SIZE; ++col) {
        for (int row = 0; row < MAT4_ROW_SIZE; ++row) {
            for (int index = 0; index < 4; ++index) {
                result[row * 4 + col] += matrix[index * 4 + col] * mat.matrix[row * 4 + index];
            }
        }
    }
    return result;
}
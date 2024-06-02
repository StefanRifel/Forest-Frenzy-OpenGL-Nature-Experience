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

mat4 mat4::operator* (const float a) const {
    mat4 result {};
    for (size_t i = 0; i < MAT4_SIZE; i++) {
        result.matrix[i] += a * matrix[i];
    }
    return result;
}

mat4 mat4::operator* (const mat4& mat) const {
    mat4 result;
    for (GLuint i = 0; i < MAT4_ROW_SIZE; ++i) {
        for (GLuint j = 0; j < MAT4_COLUMN_SIZE; ++j) {
            GLfloat sum = 0.0f;
            for (GLuint k = 0; k < MAT4_ROW_SIZE; ++k) {
                sum += matrix[k * MAT4_ROW_SIZE + i] * mat.matrix[j * MAT4_ROW_SIZE + k];
            }
            result.matrix[j * MAT4_ROW_SIZE + i] = sum;
        }
    }
    return result;
}
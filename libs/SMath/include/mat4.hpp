#ifndef MAT4_HH
#define MAT4_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>

const GLuint MAT4_SIZE = 16;
const GLuint MAT4_COLUMN_SIZE = 4;
const GLuint MAT4_ROW_SIZE = 4;

class mat4 {

    // For access with [][] operator
    class ColumnAccessor {
    public:
        ColumnAccessor(mat4& parent, int col) : parent(parent), col(col) {}

        GLfloat& operator[](int row) {
            if (row < 0 || row >= 4) {
                throw std::out_of_range("Row index out of range");
            }
            return parent.matrix[row * 4 + col];
        }

    private:
        mat4& parent;
        int col;
    };

private:
/*
    column-major order:
    | X     Y     Z      W     |
    | M[0]  M[4]  M[8]   M[12] |
    | M[1]  M[5]  M[9]   M[13] |
    | M[2]  M[6]  M[10]  M[14] |
    | M[3]  M[7]  M[11]  M[15] |
*/
    GLfloat* matrix;
    
public:

    mat4();
    //Einheitsmatrix
    mat4(GLfloat identity);
    mat4(const mat4& mat);
    mat4(const GLfloat* mat);
    ~mat4();

    friend std::ostream& operator<< (std::ostream& out, const mat4& mat);

    mat4& operator= (const mat4& mat);
    ColumnAccessor operator[](int col) {
        if (col < 0 || col >= 4) {
            throw std::out_of_range("Column index out of range");
        }
        return ColumnAccessor(*this, col);
    }

    //Skalarmultiplikation
    mat4 operator* (const float a) const;
    //Matrizenmultiplikation
    mat4 operator* (const mat4& mat) const;
};

#endif
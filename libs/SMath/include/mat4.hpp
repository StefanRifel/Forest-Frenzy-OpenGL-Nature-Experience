#ifndef MAT4_HH
#define MAT4_HH

const int MAT_N = 4;

#include <iostream>
#include <iomanip>
#include <array>

class mat4 {

private:
    // row, colum
    std::array<std::array<float, MAT_N>, MAT_N> matrix;
    
public:
    mat4();
    //Einheitsmatrix
    mat4(float identity);
    mat4(const mat4& mat);
    ~mat4();

    const float* valuePtr() const;

    friend std::ostream& operator<< (std::ostream& out, const mat4& mat);

    mat4& operator= (const mat4& mat);
    std::array<float, MAT_N>& operator[] (int index);

    //Skalarmultiplikation
    mat4 operator* (const float a) const;
    //Matrizenmultiplikation
    mat4 operator* (const mat4& mat) const;
};

#endif
#include "../include/Transformation.hpp"
#include <iostream>
#include <cmath>

void Transformation::identity(mat4& out) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            x == y ? out[x][y] = 1.0f : out[x][y] = 0.0f;
        }
    }
}

mat4 Transformation::translate(mat4& in, vec3& v) {
    /*
        create translation Matrix:
        | 1  0  0 Tx |
        | 0  1  0 Ty |
        | 0  0  1 Tz |
        | 0  0  0  1 |
    */
    mat4 translationMatrix {1.0f};
    translationMatrix[0][3] = v.x();  
    translationMatrix[1][3] = v.y();
    translationMatrix[2][3] = v.z();

    return in * translationMatrix;
}

mat4 Transformation::scale(mat4& in, vec3& v) {
    /*
        create scale Matrix:
        | S1   0   0   0 |
        |  0  S2   0   0 |
        |  0   0  S3   0 |
        |  0   0   0   1 |
    */
    mat4 scaleMatrix {1.0f};
    scaleMatrix[0][0] = v.x();  
    scaleMatrix[1][1] = v.y();
    scaleMatrix[2][2] = v.z();

    return in * scaleMatrix;
}

mat4 Transformation::rotateZ(mat4& in, GLuint angle) {
    /*
        create rotate Z Matrix:
        | cos -sin    0    0   |
        | sin  cos    0    0   |
        |   0    0    0    0   |
        |   0    0    0    1   |
    */
    mat4 rotateZMatrix {1.0f};
    float radiant = Transformation::radiant(angle);
    rotateZMatrix[0][0] = cos(radiant);  
    rotateZMatrix[0][1] = -sin(radiant);
    rotateZMatrix[1][0] = sin(radiant);
    rotateZMatrix[1][1] = cos(radiant);

    return in * rotateZMatrix;
}

mat4 Transformation::rotateX(mat4& in, GLuint angle) {
    /*
        create rotate X Matrix:
        |   0    0    0    0   |
        |   0  cos -sin    0   |
        |   0  sin  cos    0   |
        |   0    0    0    1   |
    */
    mat4 rotateXMatrix {1.0f};
    float radiant = Transformation::radiant(angle);
    rotateXMatrix[1][1] = cos(radiant);  
    rotateXMatrix[1][2] = -sin(radiant);
    rotateXMatrix[2][1] = sin(radiant);
    rotateXMatrix[2][2] = cos(radiant);

    return in * rotateXMatrix;
}

mat4 Transformation::rotateY(mat4& in, GLuint angle) {
    /*
        create rotate Z Matrix:
        | cos    0 -sin    0   |
        |   0    0    0    0   |
        |-sin    0  cos    0   |
        |   0    0    0    1   |
    */
    mat4 rotateYMatrix {1.0f};
    float radiant = Transformation::radiant(angle);
    rotateYMatrix[0][0] = cos(radiant);  
    rotateYMatrix[0][2] = sin(radiant);
    rotateYMatrix[2][0] = -sin(radiant);
    rotateYMatrix[2][2] = cos(radiant);

    return in * rotateYMatrix;
}

vec3 Transformation::normalize(const vec3& v) {
    return v * (1.0f / v.length());
}

vec3 Transformation::cross(vec3& a, vec3& b) {
    vec3 result {};
    result[0] = (a[1] * b[2]) - (a[2] * b[1]);
    result[1] = (a[2] * b[0]) - (a[0] * b[2]);
    result[2] = (a[0] * b[1]) - (a[1] * b[0]);
    return result;
}

float Transformation::dot(vec3& a, vec3& b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

mat4 Transformation::lookAt(vec3 eye, vec3 center, vec3 up) {
    /*
        create view Matrix:
        |  u'x  u'y  u'z  tx  |
        |  v'x  v'y  v'z  ty  |
        |  n'x  n'y  n'z  tz  |
        |    0    0    0   1  |
    */

    // n z
    vec3 cameraDirection {Transformation::normalize(eye - center)};
    // u x
    vec3 cameraRight {Transformation::normalize(Transformation::cross(up, cameraDirection))};
    // v y
    vec3 cameraUp {Transformation::cross(cameraDirection, cameraRight)};

    mat4 view {1.0f};
    // set right vector
    view[0][0] = cameraRight[0];
    view[0][1] = cameraRight[1];
    view[0][2] = cameraRight[2];
    
    // set up vector
    view[1][0] = cameraUp[0];
    view[1][1] = cameraUp[1];
    view[1][2] = cameraUp[2];

    // set direction vector
    view[2][0] = cameraDirection[0];
    view[2][1] = cameraDirection[1];
    view[2][2] = cameraDirection[2];

    // set translation vector
    view[0][3] = -Transformation::dot(cameraRight, eye);
    view[1][3] = -Transformation::dot(cameraUp, eye);
    view[2][3] = -Transformation::dot(cameraDirection, eye);

    return view;
}

mat4 Transformation::perspective(float fov, float aspect, float near, float far) {
    mat4 projection {1.0f};

    projection[0][0] = 1.0f / (aspect * tan(Transformation::radiant(fov) / 2.0f));
    projection[1][1] = 1.0f / tan(Transformation::radiant(fov) / 2.0f);
    projection[2][2] = -((far + near) / (far - near));
    projection[2][3] = -((2.0f * far * near) / (far - near));
    projection[3][2] = -1.0f;
    projection[3][3] = 0.0f;

    return projection;
}

float Transformation::radiant(float angle) {
    return angle * M_PI /180;
}

vec3 Transformation::calcPointOnCircle(int angle, float radius) {
    vec3 point {};
    point.x() = (float)(radius * cos(angle * M_PI /180));
    point.y() = (float)(radius * sin(angle * M_PI /180));
    return point;
}
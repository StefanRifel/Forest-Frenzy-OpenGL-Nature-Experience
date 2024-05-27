#ifndef SHADER_HH
#define SHADER_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../libs/SMath/include/mat4.hpp"
#include "../libs/SMath/include/vec3.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // the program ID
    GLuint ID;
    mat4 model;
    mat4 view;
    mat4 projection;
    
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader();

    bool createShader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setColor(vec3 color, const std::string &name);

    void setModel(mat4 model);
    void setView(mat4 view);
    void setProjection(mat4 projection);
};

#endif
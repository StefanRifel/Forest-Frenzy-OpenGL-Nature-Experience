#ifndef SHADER_HH
#define SHADER_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../libs/SMath/include/mat4.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief The Shader class encapsulates the functionality for creating, using, and managing OpenGL shaders.
 *
 * This class provides methods to load and compile vertex and fragment shaders from files, link them into a shader program,
 * and set various types of uniform variables in the shaders.
 */
class Shader {
private:
    static std::string readFile(const char *filePath);
    static GLuint compileShader(const char *source, GLenum shaderType);

public:
    // Program ID for the shader program
    GLuint ID {0};

    Shader() = default;
    /**
    * @brief Creates the shader program by loading, compiling, and linking vertex and fragment shaders.
    *
    * @param vertexPath Path to the vertex shader source file.
    * @param fragmentPath Path to the fragment shader source file.
    * @return True if the shader program was created successfully, false otherwise.
    */
    bool createShader(const char* vertexPath, const char* fragmentPath);
    /**
     * @brief Activates the shader program for rendering.
     */
    void use() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void setModel(mat4 model) const;
    void setView(mat4 view) const;
    void setProjection(mat4 projection) const;


};

#endif
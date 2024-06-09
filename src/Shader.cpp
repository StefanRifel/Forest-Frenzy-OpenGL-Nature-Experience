#include "../include/Shader.hpp"
#include "../libs/SMath/include/vec3.hpp"

void Shader::use() const {
    glUseProgram(ID);
}

bool Shader::createShader(const char* vertexPath, const char* fragmentPath) {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexSource;
    std::string fragmentSource;

    // Read shader files
    try {
        vertexSource = readFile(vertexPath);
        fragmentSource = readFile(fragmentPath);
    } catch (const std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
        return false;
    }

    // Compile shaders
    GLuint vertexShader = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
    if (!vertexShader) return false;

    GLuint fragmentShader = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
    if (!fragmentShader) return false;

    // Link shaders into a program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    GLint success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(ID, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return false;
    }

    // Clean up shaders as they're no longer needed after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

std::string Shader::readFile(const char* filePath) {
    std::ifstream file(filePath);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    file.close();

    return fileStream.str();
}

GLuint Shader::compileShader(const char* source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::"
                  << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                  << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, const vec3& value) const {
    int vec3Loc = glGetUniformLocation(ID, name.c_str());
    glUniform3f(vec3Loc, value.r(), value.g(), value.b());
}

void Shader::setModel(mat4 model) const {
    int modelLoc = glGetUniformLocation(ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.valuePtr());
}

void Shader::setView(mat4 view) const {
    int viewLoc = glGetUniformLocation(ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.valuePtr());
}

void Shader::setProjection(mat4 projection) const {
    int projectionLoc = glGetUniformLocation(ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.valuePtr());
}
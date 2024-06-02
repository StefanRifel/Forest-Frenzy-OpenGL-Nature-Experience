#ifndef MODELLODER_HH
#define MODELLODER_HH

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "../libs/SMath/include/vec3.hpp"
#include "../libs/SMath/include/vector.hpp"

#include "Vertex.hpp"

/*
    This class is responsible for loading .obj files and convert its content to:
    - v = vertex
    - vt = texture coordinate of one vertex (not implemented yet)
    - vn  = normal of one vertex
    - f = face (set of 3 indices that represent a triangle)
*/
class ModelLoader {

private:

public:
    ModelLoader();
    static bool load(const char* path, vector<Vertex>& outVertices, vector<GLuint>& outIndices);
    
    ~ModelLoader();
};

#endif
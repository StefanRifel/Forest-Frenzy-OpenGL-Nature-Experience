#ifndef MODELLODER_HH
#define MODELLODER_HH

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./Vertex.h"

#include <fstream>
#include <iostream>
#include <sstream>

/*
    This class is responsible for loading .obj files and convert its content to:
    - v = vertex
    - vt = texture coordinate of one vertex (not implemented yet)
    - vn  = normal of one vertex (not implemented yet)
    - f = face (set of 3 indices that represent a triangle)
*/
class ModelLoader {

private:
    std::vector<GLuint> tempIndices;

public:
    ModelLoader();
    static bool load(const char* path, std::vector<Vertex>& outVertices, std::vector<GLuint>& outFaces);
    
    ~ModelLoader();
};

#endif
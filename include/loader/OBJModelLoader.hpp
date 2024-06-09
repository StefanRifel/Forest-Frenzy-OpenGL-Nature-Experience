#ifndef MODEL_LOADER_HH
#define MODEL_LOADER_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../renderable/Vertex.h"
#include "../../libs/SMath/include/vector.hpp"

#include <string>

#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
/**
 * @brief The OBJModelLoader class is responsible for loading .obj files and converting their content into usable data structures.
 *
 * This class provides functionality to read and parse .obj files, extracting information about the model's geometry.
 * The .obj file format is widely used for representing 3D models and contains different types of data:
 * - 'v': Represents a vertex with its position in 3D space.
 * - 'vt': Represents the texture coordinate of a vertex (not implemented yet).
 * - 'vn': Represents the normal vector of a vertex.
 * - 'f': Represents a face, which is a set of 3 indices that define a triangle in the model.
 */
class OBJModelLoader {

public:
    static bool load(const char* path, vector<Vertex>& outVertices);
};

#endif
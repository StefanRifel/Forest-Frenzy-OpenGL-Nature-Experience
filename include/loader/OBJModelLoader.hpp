#ifndef MODEL_LOADER_HH
#define MODEL_LOADER_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../renderable/Vertex.h"
#include "../renderable/Face.h"
#include "../renderable/Material.h"

#include "AssetLoader.hpp"

#include "../../libs/SMath/include/vector.hpp"

#include <string>

#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @brief The OBJModelLoader class is responsible for loading .obj files and converting their content into usable data structures.
 *
 * This class provides functionality to read and parse .obj files, extracting information about the model's geometry.
 * The .obj file format is widely used for representing 3D models and contains different types of data:
 * - 'v': Represents a vertex with its position in 3D space.
 * - 'vt': Represents the texture coordinate of a vertex.
 * - 'vn': Represents the normal vector of a vertex.
 * - 'f': Represents a face, which is a set of 3 indices that define a triangle in the model.
 */
class OBJModelLoader {
private:
    static void loadMtl(const std::string& mtlPath, vector<Material>& materials);

public:
    static bool loadObj(const std::string& objFile, vector<Vertex>& outVertices, Face& faces, vector<Material>& materials);
};

#endif
#ifndef MODEL_LOADER_HH
#define MODEL_LOADER_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../renderable/Mesh.h"
#include "../renderable/Face.h"
#include "../renderable/Material.hpp"

#include "AssetLoader.hpp"
#include "TextureLoader.hpp"

#include "../../libs/SMath/include/vector.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

/**
 * @brief The OBJModelLoader class is responsible for loading .obj files and converting their content into usable data structures.
 *
 * This class provides functionality to read and parse .obj files, extracting information about the model's geometry.
 * The .obj file format is widely used for representing 3D models and contains different types of data:
 * - 'v': Represents a vertex with its position in 3D space.
 * - 'vt': Represents the texture coordinate of a vertex.
 * - 'vn': Represents the normal vector of a vertex.
 * - 'f': Represents a face, which is a set of 3 indices that define a triangle in the model.
 * - 'usemtl': Specifies the material to be used for the subsequent faces.
 */

class OBJModelLoader {
private:
    /**
     * @brief Creates a Mesh object from the given string data.
     *
     * @param meshString A string containing the mesh data.
     * @param outMaterials A reference to a vector of materials to be filled.
     * @param outTextures A reference to a vector of textures to be filled.
     * @return A Mesh object constructed from the meshString data.
     */
    static Mesh createMesh(const std::string &meshString, vector<Material>& outMaterials, vector<Texture>& outTextures);

    /**
     * @brief Divides an .obj file into separate meshes.
     *
     * @param filePath The path to the .obj file.
     * @param outMeshes A reference to a vector of strings to be filled with separated mesh data.
     */
    static void divideObj(const std::string &filePath, vector<std::string> &outMeshes);

public:
    static unsigned int LAST_VERTX_INDEX;  ///< The last vertex index processed
    static unsigned int LAST_NORMAL_INDEX; ///< The last normal index processed
    static unsigned int LAST_TEXTURE_INDEX; ///< The last texture index processed

    /**
     * @brief Loads an .obj file and extracts meshes, materials, and textures.
     *
     * @param objFile The path to the .obj file.
     * @param outMeshes A reference to a vector of meshes to be filled.
     * @param outMaterials A reference to a vector of materials to be filled.
     * @param outTextures A reference to a vector of textures to be filled.
     */
    static void loadObj(const std::string& objFile, vector<Mesh>& outMeshes, vector<Material>& outMaterials, vector<Texture>& outTextures);

    /**
     * @brief Loads a .mtl file and extracts materials and textures.
     *
     * @param mtlFile The path to the .mtl file.
     * @param outMaterials A reference to a vector of materials to be filled.
     * @param textures A reference to a vector of textures to be filled.
     */
    static void loadMtl(const std::string& mtlFile, vector<Material>& outMaterials, vector<Texture>& textures);
};

#endif // MODEL_LOADER_HH
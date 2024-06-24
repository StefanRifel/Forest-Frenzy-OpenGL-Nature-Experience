#ifndef TEXTURE_LOADER_HH
#define TEXTURE_LOADER_HH

#include <GL/glew.h>

#include <iostream>
#include <cstring>
#include <random>

#include "../renderable/Mesh.h"

#include "AssetLoader.hpp"

#include "../../libs/SMath/include/vector.hpp"

/**
 * @brief The TextureLoader class provides utility functions for loading textures, handling cube maps and create Terrain in OpenGL applications.
 *
 * This class encapsulates static methods to facilitate texture loading from files, including images and cube maps.
 * It also supports terrain texture loading and material texture extraction for use in rendering.
 *
 * TextureLoader relies on AssetLoader to retrieve paths to assets, ensuring textures are loaded from the correct locations.
 */
class TextureLoader {
private:
    /**
     * @brief Formats a path string to ensure consistency.
     *
     * This function ensures the path string is correctly formatted for use in file operations.
     *
     * @param c A C-style string representing the path.
     * @return A formatted std::string representing the formatted path.
     */
    static std::string formatPath(char* c);

public:
    /**
     * @brief Loads a texture from a file and returns its OpenGL texture ID.
     *
     * This function loads a texture image file and returns its OpenGL texture ID.
     *
     * @param textureFile The path to the texture file.
     * @return The OpenGL texture ID of the loaded texture.
     */
    static unsigned int loadTextureFromFile(const std::string& textureFile);

    /**
     * @brief Loads terrain textures and constructs terrain geometry.
     *
     * This function loads terrain textures and constructs terrain geometry using the provided vertices and indices.
     *
     * @param texturePath The path to the terrain texture.
     * @param terrainVertices Reference to a vector of vertices that define the terrain geometry.
     * @param indices Reference to a vector of indices that define the triangles in the terrain mesh.
     * @param numStrips Number of triangle strips in the terrain.
     * @param numTrisPerStrip Number of triangles per strip in the terrain.
     */
    static void loadTerrain(const char* texturePath, vector<Vertex>& terrainVertices, vector<unsigned int>& indices, int& numStrips, int& numTrisPerStrip);

    /**
     * @brief Loads a cubemap texture from multiple image files and assigns it to the provided OpenGL texture ID.
     *
     * This function loads a cubemap texture from six image files (representing faces) and assigns it to the provided OpenGL texture ID.
     *
     * @param faces An array of six C-style strings, each representing the path to an image file for a cubemap face.
     * @param textureID Reference to an OpenGL texture ID where the cubemap texture will be loaded.
     */
    static void loadCubeMap(vector<const char*> faces, GLuint& textureID);

    /**
     * @brief Loads textures specified in the Material structure and returns them.
     *
     * This function extracts textures specified in the Material structure and returns them as Texture objects.
     *
     * @param material Reference to the Material structure containing texture information.
     * @return A vector of Texture objects extracted from the Material structure.
     */
    static vector<Texture> loadMaterialTextures(Material &material);
};

#endif // TEXTURE_LOADER_HH
#ifndef TEXTURE_LOADER_HH
#define TEXTURE_LOADER_HH

#include <GL/glew.h>
#include <iostream>
#include <string.h>

#include "../renderable/Mesh.h"

#include "AssetLoader.hpp"

#include "../../libs/SMath/include/vector.hpp"

class TextureLoader {
private:
    static std::string formatPath(char* c);
public:
    static unsigned int loadTextureFromFile(const std::string& textureFile);
    static void loadTexture(const std::string& texturePath, GLuint& textureID);
    static void loadTerrain(const char* texturePath, vector<Vertex>& terrainVertices, vector<unsigned int>& indices, int& numStrips, int& numTrisPerStrip);
    static void simpleLoadTerrain(vector<Vertex>& terrainVertices, vector<unsigned int>& indices);
    static void loadCubemap(vector<const char*> faces, GLuint& textureID);

    static vector<Texture> loadMaterialTextures(Material &material);

};

#endif
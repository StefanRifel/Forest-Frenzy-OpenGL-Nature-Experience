#include "../../include/loader/TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/LoadImg/stb_image.h"

unsigned int TextureLoader::loadTextureFromFile(const std::string& textureFile) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(textureFile.c_str(), &width, &height, &nChannels, 0);
    if (data) {
        GLenum format;
        if (nChannels == 1)
            format =  GL_RED;
        else if (nChannels == 3)
            format = GL_RGB;
        else format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << textureFile << std::endl;
        stbi_image_free(data);
        textureID = 0; // Return 0 on failure
    }
    return textureID;
}

vector<Texture> TextureLoader::loadMaterialTextures(Material& material) {
    vector<Texture> textures;

    auto loadTexture = [&](const char* mapPath, const std::string& type) {
        if (strlen(mapPath) > 0) {
            Texture texture;
            texture.id = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath(TextureLoader::formatPath(const_cast<char*>(mapPath))));
            texture.type = type;
            texture.materialName = material.mtlName;
            if (texture.id != 0)
                textures.push_back(texture);
        }
    };

    loadTexture(material.diffuse_map, "texture_diffuse");
    loadTexture(material.normal_map, "texture_normal");
    loadTexture(material.ambient_map, "texture_ambient");
    loadTexture(material.metalness_map, "texture_metalness");
    loadTexture(material.roughness_map, "texture_roughness");

    return textures;
}

std::string TextureLoader::formatPath(char* c) {
    std::string s = c;
    return s.substr(s.find_last_of('/') + 1);
}

void TextureLoader::loadCubeMap(vector<const char*> faces, GLuint& textureID) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    for (unsigned int i = 0; i < faces.size(); i++){
        unsigned char *data = stbi_load(AssetLoader::getAssetPath(faces.at(i)).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces.at(i) << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

///<------------------------------------------------------------------------

void TextureLoader::loadTerrain(const char *texturePath, vector<Vertex>& terrainVertices, vector<unsigned int>& terrainIndices, int& numStrips, int& numTrisPerStrip) {
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath, &width, &height, &nChannels, 0);
    if (data) {
        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    float yScale = 64.0f / 256.0f, yShift = 16.0f;
    int rez = 1;
    unsigned bytePerPixel = nChannels;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            unsigned char* pixelOffset = data + (j + width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];

            // vertex
            Vertex vertex;
            vertex.position.x() = -height/2.0f + height*i/(float)height;
            vertex.position.y() = (int) y * yScale - yShift;
            vertex.position.z() = -width/2.0f + width*j/(float)width;

            // texture coordinates
            vertex.texCoords.x() = (float)j / (width - 1);
            vertex.texCoords.y() = (float)i / (height - 1);

            terrainVertices.push_back(vertex);
        }
    }
    std::cout << "Loaded " << terrainVertices.size() << " vertices" << std::endl;
    stbi_image_free(data);

    // index generation
    for(unsigned i = 0; i < height-1; i += rez)
    {
        for(unsigned j = 0; j < width; j += rez)
        {
            for(unsigned k = 0; k < 2; k++)
            {
                terrainIndices.push_back(j + width * (i + k*rez));
            }
        }
    }

    numStrips = (height-1)/rez;
    numTrisPerStrip = (width/rez)*2-2;
    std::cout << "Created lattice of " << numStrips << " strips with " << numTrisPerStrip << " triangles each" << std::endl;
    std::cout << "Created " << numStrips * numTrisPerStrip << " triangles total" << std::endl;
}

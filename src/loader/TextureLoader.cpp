#include "../../include/loader/TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/LoadImg/stb_image.h"

void TextureLoader::loadTexture(const std::string& textureFile, GLuint& textureID) {
    int width, height, channels;
    unsigned char* data = stbi_load(AssetLoader::getTexturePath(textureFile).c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << textureFile << std::endl;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //texture settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

#include <random>
void TextureLoader::simpleLoadTerrain(vector<Vertex>& terrainVertices, vector<unsigned int>& terrainIndices) {
    const int SIZE = 512;
    const int VERTEX_COUNT = 512;

    // Define the range for random heights
    const float MIN_HEIGHT = 0.0f;
    const float MAX_HEIGHT = 0.2f;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(MIN_HEIGHT, MAX_HEIGHT);

    int vertexPointer = 0;
    for(int i=0;i<VERTEX_COUNT;i++){
        for(int j=0;j<VERTEX_COUNT;j++){
            Vertex v;
            vec3 vertex;
            vertex.x() = -SIZE/2.0f + SIZE*i/(float)SIZE;
            vertex.y() = dis(gen);
            vertex.z() = -SIZE/2.0f + SIZE*j/(float)SIZE;
            v.position = vertex;

            vec3 normal;
            normal.x() = 0;
            normal.y() = 1;
            normal.z() = 0;
            v.normal = normal;

            vec2 texture;
            texture.x() = ((float)j/((float)VERTEX_COUNT - 1)) * SIZE/8;
            texture.y() = ((float)i/((float)VERTEX_COUNT - 1)) * SIZE/8;
            v.texture = texture;

            terrainVertices.push_back(v);
            vertexPointer++;
        }
    }

    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            int bottomRight = bottomLeft + 1;
            terrainIndices.push_back(topLeft);
            terrainIndices.push_back(bottomLeft);
            terrainIndices.push_back(topRight);
            terrainIndices.push_back(topRight);
            terrainIndices.push_back(bottomLeft);
            terrainIndices.push_back(bottomRight);
        }
    }
}

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
            vertex.texture.x() = (float)j / (width - 1);
            vertex.texture.y() = (float)i / (height - 1);

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

void TextureLoader::loadCubemap(vector<const char*> faces, GLuint& textureID) {
    std::string path = "../assets/textures/skybox/";
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load((path + faces.at(i)).c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap tex failed to load at path: " << faces.at(i) << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

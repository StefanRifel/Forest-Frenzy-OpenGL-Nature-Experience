#include "../../include/loader/TextureLoader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/LoadImg/stb_image.h"

void TextureLoader::loadTexture(const char* texturePath, GLuint& textureID) {
    int width, height, channels;
    unsigned char* data = stbi_load(texturePath, &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}
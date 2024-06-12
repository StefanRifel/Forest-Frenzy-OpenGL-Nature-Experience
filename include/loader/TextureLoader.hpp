#ifndef TEXTURE_LOADER_HH
#define TEXTURE_LOADER_HH

#include <GL/glew.h>
#include <iostream>

class TextureLoader {
public:
    static void loadTexture(const char* texturePath, GLuint& textureID);
};

#endif
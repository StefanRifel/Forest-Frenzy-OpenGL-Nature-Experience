#ifndef TERRAIN_HH
#define TERRAIN_HH

#include "../../libs/SMath/include/vector.hpp"

#include "typs/Vertex.h"

#include "Drawable.h"

#include "../Shader.hpp"
#include "../Camera.hpp"

#include "../../include/loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

/**
 * @brief Header file defines a Terrain class that inherits from Drawable and is used to manage and render terrain in a 3D graphics application, including methods for initializing the terrain with a texture file and drawing it using a camera
 *
 */

class Terrain : public Drawable {
private:
    GLuint textureID {0};           ///< Element Buffer Object for index data

public:
    explicit Terrain(const std::string& textureFile);
    ~Terrain() override = default;

    void draw(Camera& camera) override;
};

#endif //TERRAIN_HH

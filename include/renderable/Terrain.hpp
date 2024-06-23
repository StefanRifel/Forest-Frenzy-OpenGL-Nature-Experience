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

class Terrain : public Drawable {
private:
    GLuint textureID {0};           ///< Element Buffer Object for index data

public:
    explicit Terrain(const std::string& textureFile);
    ~Terrain() override = default;

    void draw(Camera& camera) override;
};

#endif //TERRAIN_HH

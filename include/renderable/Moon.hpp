#ifndef MOON_HH
#define MOON_HH

#include "../../libs/SMath/include/vector.hpp"

#include "typs/Vertex.h"
#include "typs/Light.h"

#include "../Shader.hpp"
#include "../Camera.hpp"

#include "Drawable.h"

#include "../../include/loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

class Moon : public Drawable {
private:
    GLuint textureID {0};

    Light light;

public:
    explicit Moon(const std::string& objFile);

    void draw(Camera& camera) const override;
    Light& getLight();
};

#endif //MOON_HH

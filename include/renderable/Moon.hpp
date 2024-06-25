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

/**
 * @brief Header defines a moon object. It manages the moon's mesh, shader, lighting, and rotation
 *
 */
class Moon {
private:
    Mesh mesh;
    Shader shader;

    Light light;
    float rotationAngle {0};

    void updateRotation(float deltaTime);
public:
    explicit Moon(const std::string& objFile);

    void draw(Camera& camera);

    Light& getLight();
};

#endif //MOON_HH

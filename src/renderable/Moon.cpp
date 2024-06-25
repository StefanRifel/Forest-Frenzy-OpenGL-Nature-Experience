#include "../../include/renderable/Moon.hpp"
#include "../../include/RenderSystem.hpp"

/**
 * @brief Class encapsulates functionality for rendering a moon object in a 3D scene. It manages loading of mesh geometry, shader programs, textures, and handles rendering transformations and lighting parameters
 */

Moon::Moon(const std::string& objFile) : mesh {objFile} {
    if (!shader.createShader(
            AssetLoader::getShaderPath("moon_vert.glsl"),
            AssetLoader::getShaderPath("moon_frag.glsl")
    )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
    }

    light.color = {0.86f, 0.93f, 0.95f};
    light.position = {-4.0f, 14.0f, 12.0f};
    light.ambient = {0.1f, 0.1f, 0.15f};
    light.diffuse = {0.8f, 0.6f, 0.5f};
    light.specular = {0.9f, 0.8f, 0.7f};

    Texture moonTexture;
    moonTexture.id = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath("brown_mud_diff_1k.jpg"));
    moonTexture.type = "moon";
    moonTexture.materialName = "brown_mud_diff_1k.jpg";

    mesh.model = Transformation::translate(mesh.model, light.position);

    mesh.textures.push_back(moonTexture);
}

void Moon::draw(Camera& camera) {
    Transformation::removeTranslation(camera.getView());
    updateRotation(camera.deltaTime);
    mesh.model = Transformation::rotateY(mesh.model, rotationAngle);

    mesh.draw(shader, camera);

    shader.setVec3("light.color", light.color);

    RenderSystem::renderMesh(mesh);
}

Light& Moon::getLight() {
    return light;
}

void Moon::updateRotation(float deltaTime) {
    rotationAngle += deltaTime * 0.02f;
    if(rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
}

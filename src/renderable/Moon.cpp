#include "../../include/renderable/Moon.hpp"

Moon::Moon(const std::string& objFile) {
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

    changePosition(light.position);

    textureID = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath("brown_mud_diff_1k.jpg"));

    OBJModelLoader::loadSimpleVertexObj(objFile, vertices, indices);

    init();
}



void Moon::draw(Camera& camera) {
    shader.use();

    // Set matrices
    shader.setProjection(camera.getPerspective());
    Transformation::removeTranslation(camera.getView());
    shader.setView(camera.getView());
    model = Transformation::rotateY(this->model, rotationAngle);
    shader.setModel(model);

    shader.setVec3("lightColor", light.color);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

Light& Moon::getLight() {
    return light;
}

void Moon::updateRotation(float deltaTime) {
    rotationAngle += deltaTime * 0.03f;
    if(rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
}

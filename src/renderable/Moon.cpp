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

    textureID = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath("brown_mud_diff_1k.jpg"));

    OBJModelLoader::loadSimpleVertexObj(objFile, vertices, indices);

    init();
}

void Moon::draw(Camera& camera) const {
    shader.use();

    // Set matrices
    shader.setProjection(camera.getPerspective());
    //Transformation::removeTranslation(camera.getView());
    shader.setView(camera.getView());
    mat4 model {1.0f};
    vec3 transform {light.position};
    model = Transformation::translate(model, transform);
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

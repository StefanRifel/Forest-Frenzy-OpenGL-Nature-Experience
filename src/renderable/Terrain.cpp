#include "../../include/renderable/Terrain.hpp"

Terrain::Terrain(const std::string& textureFile) {
    if (!shader.createShader(
            AssetLoader::getShaderPath("terrain_vert.glsl"),
            AssetLoader::getShaderPath("terrain_frag.glsl")
    )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_TERRAIN_SHADER" << std::endl;
    }

    OBJModelLoader::createSimpleTerrain(vertices, indices);

    textureID = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath(textureFile));

    init();
}

void Terrain::draw(Camera& camera) {
    shader.use();

    // Set matrices
    shader.setProjection(camera.getPerspective());
    shader.setView(camera.getView());
    shader.setModel(model);

    shader.setVec3("lightPos", vec3(-4.0f, 14.0f, 12.0f));
    shader.setVec3("viewPos", camera.getPosition());

    // Set Flashlight Properties
    shader.setVec3("flashlight.position",  camera.getPosition());
    shader.setVec3("flashlight.direction", camera.getFront());
    shader.setFloat("flashlight.cutOff", std::cos(Transformation::radiant(12.5f)));
    shader.setFloat("flashlight.outerCutOff", std::cos(Transformation::radiant(17.5f)));

    vec3 fleshLightAmbient { 0.9f, 0.9f, 0.9f};
    shader.setVec3("flashlight.ambient", fleshLightAmbient);
    vec3 fleshLightDiffuse {0.8f, 0.8f, 0.8f};
    shader.setVec3("flashlight.diffuse", fleshLightDiffuse);
    vec3 fleshLightSpecular {1.0f, 1.0f, 1.0f};
    shader.setVec3("flashlight.specular", fleshLightSpecular);

    shader.setFloat("flashlight.constant", 1.0f);
    shader.setFloat("flashlight.linear", 0.09f);
    shader.setFloat("flashlight.quadratic", 0.032f);

    shader.setBool("flashLightOn", camera.isFlashlight());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

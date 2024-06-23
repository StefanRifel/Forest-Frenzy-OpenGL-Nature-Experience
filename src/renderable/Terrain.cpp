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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

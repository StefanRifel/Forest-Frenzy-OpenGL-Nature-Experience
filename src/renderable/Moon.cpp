#include "../../include/renderable/Moon.hpp"

Moon::Moon(const std::string& objFile) {
    if (!shader.createShader(
            AssetLoader::getShaderPath("moon_vert.glsl"),
            AssetLoader::getShaderPath("moon_frag.glsl")
    )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
    }

    int index = 0;
    float offset = 2.1f;
    for (int y = -10; y < 10; y += 2) {
        for (int x = -10; x < 10; x += 2) {
            vec2 translation;
            translation.x() = (float)x * 40 / 10.0f + offset;
            translation.y() = (float)y * 40 / 10.0f + offset;
            translations[index++] = translation;
        }
    }

    light.color = {0.86f, 0.93f, 0.95f};
    light.position = {-4.0f, 14.0f, 12.0f};
    light.ambient = {0.1f, 0.1f, 0.15f};
    light.diffuse = {0.8f, 0.6f, 0.5f};
    light.specular = {0.9f, 0.8f, 0.7f};

    changePosition(light.position);

    textureID = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath("brown_mud_diff_1k.jpg"));

    OBJModelLoader::loadSimpleVertexObj(objFile, vertices, indices);

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 100, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    init();

    glBindVertexArray(this->VAO);
    // also set instance data
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1); // tell OpenGL this is an instanced vertex attribute.
}

void Moon::draw(Camera& camera) const {
    shader.use();

    // Set matrices
    shader.setProjection(camera.getPerspective());
    //Transformation::removeTranslation(camera.getView());
    shader.setView(camera.getView());
    shader.setModel(model);

    shader.setVec3("lightColor", light.color);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
    glDrawArraysInstanced(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()), 100);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

Light& Moon::getLight() {
    return light;
}

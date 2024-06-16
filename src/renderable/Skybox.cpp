#include "../../include/renderable/Skybox.hpp"

Skybox::Skybox(const vector<Vertex>& vertices)
        : Mesh {vertices} {
    if(!shader.createShader(AssetLoader::getShaderPath("skybox_vert.glsl"), AssetLoader::getShaderPath("skybox_frag.glsl"))) {
        std::cerr << "ERROR::SKYBOX::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Skybox::draw(Camera& camera) const {
    glDepthFunc(GL_LEQUAL);
    Mesh::draw(camera);
    shader.setInt("skybox", 0);
    Transformation::removeTranslation(camera.getView());
    shader.setView(camera.getView());

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}
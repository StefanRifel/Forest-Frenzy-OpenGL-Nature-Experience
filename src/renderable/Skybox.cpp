#include "../../include/renderable/Skybox.hpp"

Skybox::Skybox(const std::string& objFile)
        : Mesh {objFile} {
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

void Skybox::setCubeMap() {
    vector<const char*> skyboxFaces;
    skyboxFaces.push_back("right.png");
    skyboxFaces.push_back("left.png");
    skyboxFaces.push_back("top.png");
    skyboxFaces.push_back("bottom.png");
    skyboxFaces.push_back("front.png");
    skyboxFaces.push_back("back.png");
    TextureLoader::loadCubemap(skyboxFaces, textureID);
}
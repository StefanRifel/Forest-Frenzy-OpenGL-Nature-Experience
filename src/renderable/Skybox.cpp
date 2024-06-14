#include "../../include/renderable/Skybox.hpp"

Skybox::Skybox(const vector<Vertex>& vertices)
        : Mesh {vertices} {
    if(!shader.createShader("../shaders/skybox_vert.glsl", "../shaders/skybox_frag.glsl")) {
        std::cerr << "ERROR::TREE::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Skybox::draw() const {
    Mesh::draw();
    //glDepthFunc(GL_LEQUAL);
    shader.setInt("skybox", 0);


    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}
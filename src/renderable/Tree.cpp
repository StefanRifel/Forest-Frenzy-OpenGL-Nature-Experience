#include "../../include/renderable/Tree.hpp"

Tree::Tree(const vector<Vertex>& vertices)
    : Mesh {vertices} {
    if(!shader.createShader(AssetLoader::getShaderPath("jacaranda_tree_vert.glsl"), AssetLoader::getShaderPath("jacaranda_tree_frag.glsl"))) {
        std::cerr << "ERROR::TREE::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Tree::draw(Camera& camera) const {
    Mesh::draw(camera);
    shader.setVec3("objColor", color);
/*
    vec3 lightColor {1.0f, 1.0f, 1.0f};
    shader.setVec3("lightColor", lightColor);

    vec3 lightPos {0.0, 0.0, 6.0};
    shader.setVec3("lightPos", lightPos);

    vec3 cameraPos {0.0f, 0.0f, 3.0f};
    shader.setVec3("viewPos", cameraPos);

    shader.setVec3("material.ambient", material.ambient);
    shader.setVec3("material.diffuse", material.diffuse);
    shader.setVec3("material.specular", material.specular);
    shader.setFloat("material.shininess", material.shininess);

    shader.setInt("texture1", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
*/
    // add Transformation here

    shader.setView(camera.getView());

    mat4 model {1.0f};
    vec3 translate {0.0f, 0.1f, 0.0f};
    model = Transformation::translate(model, translate);

    shader.setModel(model);
    //shader.setVec3("cameraPos", camera.getPosition());


    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}
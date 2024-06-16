#include "../../include/renderable/Tree.hpp"

Tree::Tree(const std::string& objFile)
    : Mesh {objFile} {
    if(!shader.createShader(AssetLoader::getShaderPath("jacaranda_tree_vert.glsl"), AssetLoader::getShaderPath("jacaranda_tree_frag.glsl"))) {
        std::cerr << "ERROR::TREE::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Tree::draw(Camera& camera) const {
    Mesh::draw(camera);
    shader.setView(camera.getView());

    // model transformation
    mat4 model {1.0f};
    vec3 translate {0.0f, 0.1f, 0.0f};
    model = Transformation::translate(model, translate);
    shader.setModel(model);

    // material
    shader.setVec3("material.emissive", materials.at(2).emissive);
    shader.setVec3("material.ambient", materials.at(2).ambient);
    shader.setVec3("material.diffuse", materials.at(2).diffuse);
    shader.setVec3("material.specular", materials.at(2).specular);
    shader.setFloat("material.shininess", materials.at(2).shininess);

    vec3 lightColor {1.0f, 1.0f, 1.0f};
    shader.setVec3("lightColor", lightColor);

    vec3 lightPos {0.0, 5.0, 6.0};
    shader.setVec3("lightPos", lightPos);

    shader.setVec3("viewPos", camera.getPosition());

    shader.setInt("texture1", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}
#include "../../include/Tree.hpp"

Tree::Tree(const vector<Vertex>& vertices, const vector<GLuint>& indices, const vector<vec3>& normals)
    : Mesh {vertices, indices, normals} {
    if(!shader.createShader("../shaders/mesh_vert.glsl", "../shaders/lighting_frag.glsl")) {
        std::cerr << "ERROR::TREE::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Tree::draw() const {
    Mesh::draw();
    shader.setVec3("objColor", color);

    vec3 lightColor {1.0f, 1.0f, 1.0f};
    shader.setVec3("lightColor", lightColor);

    // add Transformation here
    mat4 model {1.0f};
    vec3 scale {0.5, 0.5, 0.5};
    model = Transformation::scale(model, scale);
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
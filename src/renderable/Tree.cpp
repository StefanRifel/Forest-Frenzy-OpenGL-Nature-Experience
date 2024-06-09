#include "../../include/Tree.hpp"

Tree::Tree(vector<Vertex> vertices, vector<GLuint> indices) : Mesh {vertices, indices} {

}

Tree::~Tree() {

}

void Tree::draw(Shader shader) const {
    Mesh::draw(shader);

    mat4 model {1.0f};
    
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
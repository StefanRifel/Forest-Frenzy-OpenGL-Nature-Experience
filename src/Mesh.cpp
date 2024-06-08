#include "../include/Mesh.hpp"

Mesh::Mesh() {

}

Mesh::Mesh(vector<Vertex> vertices) : RenderableObject {vertices} {

}

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices) : RenderableObject {vertices, indices} {

}

Mesh::~Mesh() {

}

void Mesh::draw(Shader shader) const {
    RenderableObject::draw(shader);

    mat4 model {1.0f};
    
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLES, getIndicesSize(), GL_UNSIGNED_INT, 0);
}
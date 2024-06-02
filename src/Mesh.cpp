#include "../include/Mesh.hpp"

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<Vertex> vertices) : RenderableObject {vertices} {

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) : RenderableObject {vertices, indices} {

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
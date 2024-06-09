#include "../../include/Tree.hpp"

Tree::Tree(const vector<Vertex>& vertices, const vector<GLuint>& indices) : Mesh {vertices, indices} {

}

void Tree::draw() const {
    Mesh::draw();

    // add Transformation here
    mat4 model {1.0f};
    vec3 scale {0.5, 0.5, 0.5};
    model = Transformation::scale(model, scale);
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
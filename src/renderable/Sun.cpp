#include "../../include/Sun.hpp"

Sun::Sun(const vector<Vertex> &vertices, const vector<GLuint> &indices) : Mesh(vertices, indices) {

}

void Sun::draw() const {
    Mesh::draw();

    // add Transformation here
    mat4 model {1.0f};
    vec3 scale {0.5, 0.5, 0.5};
    vec3 position {2.0, 2.0, 2.0};
    model = Transformation::scale(model, scale);
    model = Transformation::translate(model, position);
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

}

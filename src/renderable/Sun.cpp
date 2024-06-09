#include "../../include/Sun.hpp"

Sun::Sun(const vector<Vertex> &vertices)
    : Mesh(vertices) {
    if(!shader.createShader("../shaders/mesh_vert.glsl", "../shaders/sun_frag.glsl")) {
        std::cerr << "ERROR::SUN::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Sun::draw() const {
    Mesh::draw();
    shader.setVec3("objColor", color);

    // add Transformation here
    mat4 model {1.0f};
    //vec3 scale {0.5, 0.5, 0.5};
    vec3 position {0.0, 2, 4.0};
    //model = Transformation::scale(model, scale);
    model = Transformation::translate(model, position);
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

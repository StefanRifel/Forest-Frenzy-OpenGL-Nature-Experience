#include "../../include/renderable/Sun.hpp"

Sun::Sun(const vector<Vertex> &vertices)
    : Mesh(vertices) {
    if(!shader.createShader(AssetLoader::getShaderPath("mesh_vert.glsl"), AssetLoader::getShaderPath("sun_frag.glsl"))) {
        std::cerr << "ERROR::SUN::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Sun::draw(Camera& camera) const {
    Mesh::draw(camera);
    shader.setVec3("objColor", color);
    shader.setView(camera.getView());
    // add Transformation here
    mat4 model {1.0f};
    //vec3 scale {0.5, 0.5, 0.5};
    vec3 position {0.0, 5.0, 6.0};
    //model = Transformation::scale(model, scale);
    model = Transformation::translate(model, position);
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

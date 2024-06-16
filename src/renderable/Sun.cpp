#include "../../include/renderable/Sun.hpp"

Sun::Sun(const std::string& objFile)
    : Mesh(objFile) {
    if(!shader.createShader(AssetLoader::getShaderPath("mesh_vert.glsl"), AssetLoader::getShaderPath("sun_frag.glsl"))) {
        std::cerr << "ERROR::SUN::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Sun::draw(Camera& camera) const {
    Mesh::draw(camera);
    shader.setView(camera.getView());

    // model transformation
    mat4 model {1.0f};
    vec3 position {0.0, 20.0, 10.0};
    model = Transformation::translate(model, position);
    shader.setModel(model);

    // material

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

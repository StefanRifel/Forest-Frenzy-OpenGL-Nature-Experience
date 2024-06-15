#include "../../include/renderable/Terrain.hpp"

Terrain::Terrain(const vector<Vertex>& vertices,  const vector<GLuint>& indices, int& numStrips, int& numTrisPerStrip)
        : Mesh {vertices, indices}, numStrips {numStrips}, numTrisPerStrip {numTrisPerStrip} {
    if(!shader.createShader("../shaders/terrain_vert.glsl", "../shaders/terrain_frag.glsl")) {
        std::cerr << "ERROR::TREE::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

Terrain::Terrain(const vector<Vertex> &vertices, const vector<GLuint> &indices) : Mesh(vertices, indices) {
    if(!shader.createShader("../shaders/terrain_vert.glsl", "../shaders/terrain_frag.glsl")) {
        std::cerr << "ERROR::TREE::FAILED_TO_CREATE_SHADER" << std::endl;
    }
}

void Terrain::draw(Camera& camera) const {
    Mesh::draw(camera);

    shader.setView(camera.getView());

    shader.setVec3("objColor", color);

    shader.setInt("texture1", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // add Transformation here
    mat4 model {1.0f};
    //vec3 scale {5, 5, 5};
    //model = Transformation::scale(model, scale);
    shader.setModel(model);

    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(0xFFFF);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

    //glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    /*
    for(unsigned strip = 0; strip < numStrips; strip++)
    {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                       numTrisPerStrip+2,   // number of indices to render
                       GL_UNSIGNED_INT,     // index data type
                       (void*)(sizeof(unsigned) * (numTrisPerStrip+2) * strip)); // offset to starting index
    }
    */
}

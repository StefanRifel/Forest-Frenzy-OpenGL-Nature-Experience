#include "../../include/renderable/Terrain.hpp"

Terrain::Terrain(const std::string& textureFile) {
    if (!shader.createShader(
            AssetLoader::getShaderPath("terrain_vert.glsl"),
            AssetLoader::getShaderPath("terrain_frag.glsl")
    )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
    }

    init();

    setUpTerrain(textureFile);
}

bool Terrain::init() {
    OBJModelLoader::createSimpleTerrain(vertices, indices);

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices.at(0)), GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)nullptr
    );

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)(sizeof(vec3))
    );

    // Texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)(2 * sizeof(vec3))
    );

    //EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);

    return true;
}

void Terrain::setUpTerrain(const std::string& textureFile) {
    textureID = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath(textureFile));
}

void Terrain::draw(Camera& camera) const {
    shader.use();

    // Set matrices
    shader.setProjection(camera.getPerspective());
    shader.setView(camera.getView());
    mat4 model {1.0f};
    shader.setModel(model);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

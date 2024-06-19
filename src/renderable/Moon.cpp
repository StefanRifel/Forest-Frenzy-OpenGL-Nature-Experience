#include "../../include/renderable/Moon.hpp"

Moon::Moon(const std::string& objFile) {
    if (!shader.createShader(
            AssetLoader::getShaderPath("moon_vert.glsl"),
            AssetLoader::getShaderPath("moon_frag.glsl")
    )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
    }

    if (!init(objFile)) {
        std::cerr << "Failed to initialize Skybox" << std::endl;
    }

    light.position = {0.0f, 13.0f, -15.0f};
    light.ambient = {0.1f, 0.1f, 0.15f};
    light.diffuse = {0.8f, 0.6f, 0.5f};
    light.specular = {0.9f, 0.8f, 0.7f};


    textureID = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath("brown_mud_diff_1k.jpg"));
}

bool Moon::init(const std::string& objFile) {
    if(!OBJModelLoader::loadSimpleObj(objFile, vertices, indices)) {
        return false;
    }

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO for position
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &(vertices.at(0)), GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(vec3),
            (void*)nullptr
    );

    //EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);

    return true;
}

Light& Moon::getLight() {
    return light;
}

void Moon::draw(Camera& camera) const {
    shader.use();

    // Set matrices
    shader.setProjection(camera.getPerspective());
    Transformation::removeTranslation(camera.getView());
    shader.setView(camera.getView());
    mat4 model {1.0f};
    vec3 transform {light.position};
    model = Transformation::translate(model, transform);
    shader.setModel(model);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
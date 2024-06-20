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

    light.color = {0.86f, 0.93f, 0.95f};
    light.position = {-4.0f, 14.0f, 12.0f};
    light.ambient = {0.1f, 0.1f, 0.15f};
    light.diffuse = {0.8f, 0.6f, 0.5f};
    light.specular = {0.9f, 0.8f, 0.7f};


    textureID = TextureLoader::loadTextureFromFile(AssetLoader::getAssetPath("brown_mud_diff_1k.jpg"));
}

bool Moon::init(const std::string& objFile) {
    if(!OBJModelLoader::loadSimpleVertexObj(objFile, vertices, indices)) {
        return false;
    }

    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO for vertex data
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), &(vertices.at(0)), GL_STATIC_DRAW);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
            0,                 ///< location attribute number in vertex shader
            3,                  ///< size of the vertex attribute
            GL_FLOAT,           ///< type of the data
            GL_FALSE,      ///< if we want the data to be normalized
            sizeof(Vertex),    ///< stride and tells us the space between consecutive vertex attributes
            (void*)nullptr    ///< offset of where the position data begins in the buffer
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


    // Unbind VAO
    glBindVertexArray(0);
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

    shader.setVec3("lightColor", light.color);
    shader.setFloat("time", glfwGetTime());

    glBindTexture(GL_TEXTURE_2D, textureID);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1024, 768, 0, GL_RGBA, GL_FLOAT, NULL);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
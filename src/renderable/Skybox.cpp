#include "../../include/renderable/Skybox.hpp"

Skybox::Skybox(const std::string& objFile) {
    if (!shader.createShader(
            AssetLoader::getShaderPath("skybox_vert.glsl"),
            AssetLoader::getShaderPath("skybox_frag.glsl")
        )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
    }

    if (!init(objFile)) {
        std::cerr << "Failed to initialize Skybox" << std::endl;
    }

    setCubeMap();
}

bool Skybox::init(const std::string& objFile) {
    if(!OBJModelLoader::loadSimpleVec3Obj(objFile, vertices, indices)) {
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

void Skybox::setCubeMap() {
    vector<const char*> skyboxFaces;
    skyboxFaces.push_back("right.png");
    skyboxFaces.push_back("left.png");
    skyboxFaces.push_back("bottom.png");
    skyboxFaces.push_back("top.png");
    skyboxFaces.push_back("front.png");
    skyboxFaces.push_back("back.png");

    TextureLoader::loadCubeMap(skyboxFaces, textureID);
}

void Skybox::draw(Camera& camera) const {
    // Make sure depth test passes when values are equal to depth buffer's content
    glDepthFunc(GL_LEQUAL);
    shader.use();

    // Set matrices
    shader.setProjection(camera.getPerspective());
    Transformation::removeTranslation(camera.getView());
    shader.setView(camera.getView());
    mat4 model {1.0f};
    model = Transformation::rotateX(model, 180);
    shader.setModel(model);



    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glDepthFunc(GL_LESS);
}

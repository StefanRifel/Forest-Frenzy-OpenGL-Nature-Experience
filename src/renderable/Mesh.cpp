#include "../../include/renderable/Mesh.h"
#include "../../include/loader/OBJModelLoader.hpp"

Mesh::Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures, Material& material)
        : vertices {vertices}, indices {indices}, textures(textures), material(material) {
}

Mesh::Mesh(const std::string &objFile) {
    OBJModelLoader::loadSimpleVertexObj(objFile, vertices, indices);
}

Mesh::~Mesh() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
    if (INSTANCE_BUFFER != 0) {
        glDeleteBuffers(1, &INSTANCE_BUFFER);
    }
}

void Mesh::draw(Shader &shader, Camera &camera) const {
    shader.use();

    // Set matrices
    shader.setProjection(camera.getPerspective());
    shader.setView(camera.getView());
    shader.setModel(model);

    // Set camera position
    shader.setVec3("viewPos", camera.getPosition());

    // Set light properties
    vec3 lightAmbient {0.1f, 0.1f, 0.15f};
    shader.setVec3("light.ambient", lightAmbient);
    vec3 lightDiffuse {0.8f, 0.6f, 0.5f};
    shader.setVec3("light.diffuse", lightDiffuse);
    vec3 lightSpecular {0.9f, 0.8f, 0.7f};
    shader.setVec3("light.specular", lightSpecular);
    vec3 lightPos {-4.0f, 14.0f, 12.0f};
    shader.setVec3("light.position", lightPos);

    // Set Flashlight Properties
    shader.setVec3("flashlight.position",  camera.getPosition());
    shader.setVec3("flashlight.direction", camera.getFront());
    shader.setFloat("flashlight.cutOff", std::cos(Transformation::radiant(12.5f)));
    shader.setFloat("flashlight.outerCutOff", std::cos(Transformation::radiant(17.5f)));

    vec3 fleshLightAmbient { 0.9f, 0.9f, 0.9f};
    shader.setVec3("flashlight.ambient", fleshLightAmbient);
    vec3 fleshLightDiffuse {0.8f, 0.8f, 0.8f};
    shader.setVec3("flashlight.diffuse", fleshLightDiffuse);
    vec3 fleshLightSpecular {1.0f, 1.0f, 1.0f};
    shader.setVec3("flashlight.specular", fleshLightSpecular);

    shader.setFloat("flashlight.constant", 1.0f);
    shader.setFloat("flashlight.linear", 0.09f);
    shader.setFloat("flashlight.quadratic", 0.032f);

    shader.setBool("flashLightOn", camera.isFlashlight());

    if(material.mtlName[0] != '\0') {
        // Set material properties
        shader.setVec3("material.emissive", material.emissive);
        shader.setVec3("material.ambient", material.ambient);
        shader.setVec3("material.diffuse", material.diffuse);
        shader.setVec3("material.specular", material.specular);
        shader.setFloat("material.shininess", material.shininess);
    }

    // Bind textures
    for (const auto& texture : textures) {
        std::string uniformName = "textures." + texture.type;
        glUniform1i(glGetUniformLocation(shader.ID, uniformName.c_str()), texture.id - 1);
        glActiveTexture(GL_TEXTURE0 + texture.id - 1);
        glBindTexture(GL_TEXTURE_2D, texture.id);
    }
}

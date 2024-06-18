#include <utility>

#include "../../include/renderable/Mesh.h"

Mesh::Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures, Material& material) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->material = material;
    setupMesh();
}

void Mesh::Draw(Shader &shader, Camera &camera) const {
    shader.use();

    // Set Matrix's
    shader.setProjection(camera.getPerspective());
    shader.setView(camera.getView());
    mat4 model {1.0f};
    shader.setModel(model);

    // Set camera
    shader.setVec3("viewPos", camera.getPosition());

    // Set light
    vec3 lightAmbient {0.2f, 0.2f, 0.2f};
    shader.setVec3("light.ambient", lightAmbient);
    vec3 lightDiffuse {0.5f, 0.5f, 0.5f};
    shader.setVec3("light.diffuse", lightDiffuse);
    vec3 lightSpecular {1.0f, 1.0f, 1.0f};
    shader.setVec3("light.specular", lightSpecular);
    vec3 lightPos {0.0f, 10.0f, -5.0f};
    shader.setVec3("light.position", lightPos);

    // Set material properties
    shader.setVec3("material.ambient", material.ambient);
    shader.setVec3("material.diffuse", material.diffuse);
    shader.setVec3("material.specular", material.specular);
    shader.setFloat("material.shininess", material.shininess);

    // Bind textures
    //std::cout << "---------------------" << std::endl;
    for (auto& a: textures) {
        //std::cout << "ID: " << a.id << " TYPE: " << a.type << std::endl;
        glActiveTexture(GL_TEXTURE0 + a.id - 1);
        glBindTexture(GL_TEXTURE_2D, a.id);
    }
    //std::cout << "---------------------" << std::endl;
    // Draw mesh
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
    glBindVertexArray(0);

    // Always good practice to reset to default after configuration
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh() {
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO for Vertex information's
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

    // Texture
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)(2 * sizeof(vec3))
    );

    if(indices.size() != 0) {
        //EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
}
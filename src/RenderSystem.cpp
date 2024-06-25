#include "../include/RenderSystem.hpp"

unsigned int RenderSystem::AMOUNT = 4;
mat4* RenderSystem::MODEL_MATRICES = new mat4[AMOUNT];

void RenderSystem::renderMesh(Mesh& mesh) {

    if(mesh.VAO == 0) {
        // Generate and bind VAO
        glGenVertexArrays(1, &mesh.VAO);
        glBindVertexArray(mesh.VAO);

        // Generate and bind VBO for vertex data
        glGenBuffers(1, &mesh.VBO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(mesh.vertices.size() * sizeof(Vertex)), &(mesh.vertices.at(0)), GL_STATIC_DRAW);

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

        // Generate and bind EBO for index data, if indices are present
        if(mesh.indices.size() != 0) {
            //EBO
            glGenBuffers(1, &mesh.EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices.at(0)), GL_STATIC_DRAW);
        }

        // Unbind VAO
        glBindVertexArray(0);
    }

    glBindVertexArray(mesh.VAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh.vertices.size()));

    // Reset to default
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void RenderSystem::renderInstancedMesh(Mesh& mesh) {

    if(MODEL_MATRICES[0][0][0] == 0) {
        createModelMatrices();
    }

    if(mesh.VAO == 0) {
        // Generate and bind VAO
        glGenVertexArrays(1, &mesh.VAO);
        glBindVertexArray(mesh.VAO);

        // Generate and bind VBO for vertex data
        glGenBuffers(1, &mesh.VBO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(mesh.vertices.size() * sizeof(Vertex)), &(mesh.vertices.at(0)), GL_STATIC_DRAW);

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

        glGenBuffers(1, &mesh.BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.BUFFER);
        glBufferData(GL_ARRAY_BUFFER, RenderSystem::AMOUNT * sizeof(mat4), RenderSystem::MODEL_MATRICES[0].valuePtr(), GL_STATIC_DRAW);

        for (unsigned int i = 0; i < 4; i++) {
            glEnableVertexAttribArray(3 + i);
            glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(i * sizeof(vec4)));
            glVertexAttribDivisor(3 + i, 1);
        }

        // Generate and bind EBO for index data, if indices are present
        if(mesh.indices.size() != 0) {
            //EBO
            glGenBuffers(1, &mesh.EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices.at(0)), GL_STATIC_DRAW);
        }

        // Unbind VAO
        glBindVertexArray(0);
    }

    //glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh.vertices.size()));

    glBindVertexArray(mesh.VAO);
    glDrawArraysInstanced(
            GL_TRIANGLES, 0, static_cast<GLsizei>(mesh.vertices.size()), RenderSystem::AMOUNT
    );

    // Reset to default
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void RenderSystem::createModelMatrices() {
    for (int i = 0; i < AMOUNT; ++i) {
        mat4 model {1.0f};
        vec3 translate {static_cast<GLfloat>(i+ 1), static_cast<GLfloat>(i + 1), static_cast<GLfloat>(i + 1)};
        model = Transformation::translate(model, translate);
        MODEL_MATRICES[i] = model;
    }

    for (int i = 0; i < 16; ++i) {
        std::cout << MODEL_MATRICES[1].valuePtr()[i] << std::endl;
    }
}

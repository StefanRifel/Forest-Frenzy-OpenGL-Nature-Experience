#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../Camera.hpp"
#include "../Shader.hpp"

#include "typs/Vertex.h"

#include "../../libs/SMath/include/vector.hpp"

class Drawable {
public:
    GLuint VAO {0};         ///< Vertex Array Object for the mesh
    GLuint VBO {0};         ///< Vertex Buffer Object for vertex data
    GLuint EBO {0};         ///< Element Buffer Object for index data

    vector<Vertex> vertices;  ///< List of vertices in the mesh
    vector<GLuint> indices;   ///< List of indices for indexed drawing

    mat4 model{1.0f};

    Shader shader;

    virtual ~Drawable() {
        if (VAO != 0) {
            glDeleteVertexArrays(1, &VAO);
        }
        if (VBO != 0) {
            glDeleteBuffers(1, &VBO);
        }
        if (EBO != 0) {
            glDeleteBuffers(1, &EBO);
        }
    }

    void changePosition(vec3& transform) {
        model = Transformation::translate(model, transform);
    }

    void scale(vec3& scale) {
        model = Transformation::scale(model, scale);
    }

    virtual void draw(Camera& camera) = 0;

    void init() {

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

        //EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);

        // Unbind VAO
        glBindVertexArray(0);
    }
};

#endif //DRAWABLE_H

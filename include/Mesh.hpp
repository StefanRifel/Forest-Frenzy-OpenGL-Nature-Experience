#ifndef RENDERABLE_OBJECT_HH
#define RENDERABLE_OBJECT_HH

#include "Vertex.h"
#include "Shader.hpp"

#include "Transformation.hpp"

#include "../libs/SMath/include/mat4.hpp"
#include "../libs/SMath/include/vector.hpp"

/**
 * @brief The Mesh class represents a 3D object that can be rendered in a graphics context.
 *
 * This class encapsulates the necessary data and functionality to render a 3D object using OpenGL.
 * It manages the object's vertex data, indices, color, and the OpenGL buffers needed for rendering.
 *
 * The Mesh class can be subclassed to create more specific types of renderable objects
 * with additional features or behaviors.
 *
 * @note The class assumes that OpenGL context and GLEW initialization have been done prior to creating instances.
 */
class Mesh {

private:
    void init();

protected:
    GLuint VAO {0}, VBO {0}, EBO {0};
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vec3 color;

public:
    Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices);
    Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices, const vec3& color);
    virtual ~Mesh() = default;

    virtual void draw(Shader shader) const;
    void setColor(vec3 color);
}; 

#endif
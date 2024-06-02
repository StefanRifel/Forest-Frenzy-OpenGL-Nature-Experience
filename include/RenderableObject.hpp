#ifndef RENDERABLEOBJECT_HH
#define RENDERABLEOBJECT_HH

#include <vector>
#include "Vertex.h"
#include "Shader.hpp"
#include "Transformation.hpp"
#include "../libs/SMath/include/mat4.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class RenderableObject {

private:
    GLuint VAO, VBO, EBO;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    vec3 color;
    void init();
public:
    RenderableObject();
    RenderableObject(std::vector<Vertex> vertices);
    RenderableObject(std::vector<Vertex> vertices, vec3 color);
    RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices, vec3 color);
    virtual ~RenderableObject();

    virtual void draw(Shader shader) const;
    void setColor(vec3 color);

    const std::vector<Vertex>& getVertices() const;
    const std::vector<GLuint>& getIndices() const;

    const std::size_t getIndicesSize() const;
    const std::size_t getVerticiesSize() const;

    void setVertices(std::vector<Vertex> vertices);
    void setVertex(Vertex vertex);
}; 

#endif
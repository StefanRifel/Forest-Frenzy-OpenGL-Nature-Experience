#ifndef RENDERABLEOBJECT_HH
#define RENDERABLEOBJECT_HH

#include <vector>
#include "Vertex.h"
#include "Shader.hpp"
#include "Transformation.hpp"
#include "../libs/SMath/include/mat4.hpp"
#include "../libs/SMath/include/vector.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class RenderableObject {

private:
    GLuint VAO, VBO, EBO;
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vec3 color;
    void init();
public:
    RenderableObject();
    explicit RenderableObject(vector<Vertex> vertices);
    RenderableObject(vector<Vertex> vertices, vec3 color);
    RenderableObject(vector<Vertex> vertices, vector<GLuint> indices);
    RenderableObject(vector<Vertex> vertices, vector<GLuint> indices, vec3 color);
    virtual ~RenderableObject();

    virtual void draw(Shader shader) const;
    void setColor(vec3 color);

    const vector<Vertex>& getVertices() const;
    const vector<GLuint>& getIndices() const;

    const std::size_t getIndicesSize() const;
    const std::size_t getVerticiesSize() const;

    void setVertices(vector<Vertex> vertices);
    void setVertex(Vertex vertex);
}; 

#endif
#include "../include/RenderableObject.hpp"

RenderableObject::RenderableObject() : color {0.04f, 0.38f, 0.69f} {
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices) : color {0.04f, 0.38f, 0.69f}, vertices {vertices} {
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices, vec3 color) : color {0.04f, 0.38f, 0.69f}, vertices {vertices} {
    setColor(color);
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices) : color {0.04f, 0.38f, 0.69f}, vertices {vertices}, indices {indices} {
    init();
}

RenderableObject::RenderableObject(std::vector<Vertex> vertices, std::vector<GLuint> indices, vec3 color) : color {color}, vertices {vertices}, indices {indices} {
    init();
}

RenderableObject::~RenderableObject() {

}

void RenderableObject::init() {
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO for Position
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                      // location attribute number in vertex shader  
        3,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        sizeof(Vertex),         // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,                      
        3,                    
        GL_FLOAT,              
        GL_FALSE,            
        sizeof(Vertex),        
        (void*)(sizeof(vec3))  
    );
    glEnableVertexAttribArray(1);

    if(indices.size() != 0) {
        //EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);
    }
}

    void RenderableObject::draw(Shader shader) const {
    shader.use();
    glBindVertexArray(VAO);

    float vertexFragColor = glGetUniformLocation(shader.ID, "fragColor");
    glUniform3f(vertexFragColor, color.r(), color.g(), color.b());
    std::cout << "r: " << color.r() << " g: " << color.g() << " b: " << color.b() << std::endl;
}

void RenderableObject::setColor(vec3 color) {
    this->color.x() = ((100.0f / 255) * color.x()) / 100;
    this->color.y() = ((100.0f / 255) * color.y()) / 100;
    this->color.z() = ((100.0f / 255) * color.z()) / 100;
}

const std::size_t RenderableObject::getIndicesSize() const {
    return indices.size();
}

void RenderableObject::setVertices(std::vector<Vertex> vertices) {
    this->vertices = vertices;
}

const std::size_t RenderableObject::getVerticiesSize() const {
    return vertices.size();
}

void RenderableObject::setVertex(Vertex vertex) {
    this->vertices.push_back(vertex);
}

const std::vector<Vertex>& RenderableObject::getVertices() const {
    return vertices;
}

const std::vector<GLuint>& RenderableObject::getIndices() const {
    return indices;
}
#include "../../include/Mesh.hpp"

Mesh::Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices)
    : color {0.04f, 0.38f, 0.69f}, vertices {vertices}, indices {indices} {
    init();
}

Mesh::Mesh(const vector<Vertex>& vertices, const vector<GLuint>& indices, const vec3& color)
    : color {color}, vertices {vertices}, indices {indices} {
    init();
}

bool Mesh::init() {
    if(!shader.createShader("../shaders/shader_vert.glsl", "../shaders/shader_frag.glsl")) {
        std::cerr << "ERROR::SCENE::FAILED_TO_CREATE_SHADER" << std::endl;
        return false;
    }

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO for Position
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices.at(0)), GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                      // location attribute number in vertex shader
        3,                       // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,          // if we want the data to be normalized
        sizeof(Vertex),        // stride and tells us the space between consecutive vertex attributes
        (void*)nullptr        // offset of where the position data begins in the buffer
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
    return true;
}

    void Mesh::draw() const {
    shader.use();
    glBindVertexArray(VAO);

    float vertexFragColor = glGetUniformLocation(shader.ID, "fragColor");
    glUniform3f(vertexFragColor, color.r(), color.g(), color.b());
}

void Mesh::setColor(vec3 color) {
    this->color.x() = ((100.0f / 255) * color.x()) / 100;
    this->color.y() = ((100.0f / 255) * color.y()) / 100;
    this->color.z() = ((100.0f / 255) * color.z()) / 100;
}

Shader &Mesh::getShader() {
    return shader;
}

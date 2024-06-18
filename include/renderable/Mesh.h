#ifndef MESH_H
#define MESH_H

#include <string>
#include "../../libs/SMath/include/vector.hpp"

#include "Vertex.h"
#include "Texture.h"
#include "Material.hpp"

#include "../Shader.hpp"
#include "../Camera.hpp"

class Mesh {
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    Material material;
    GLuint VAO{};

    Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures, Material& material);
    ~Mesh() = default;
    void Draw(Shader &shader, Camera &camera) const;

private:
    GLuint VBO{}, EBO{};

    void setupMesh();
};

#endif

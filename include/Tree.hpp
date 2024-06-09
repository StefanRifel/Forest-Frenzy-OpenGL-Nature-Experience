#ifndef MESH_HH
#define MESH_HH

#include "Mesh.hpp"

#include "../libs/SMath/include/vec3.hpp"

class Tree : public Mesh {

public:
    Tree(vector<Vertex> vertices, vector<GLuint> indices);
    ~Tree() override;
    void draw(Shader shader) const override;
};

#endif
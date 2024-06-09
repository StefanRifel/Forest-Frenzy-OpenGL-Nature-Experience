#ifndef MESH_HH
#define MESH_HH

#include "Mesh.hpp"

class Tree : public Mesh {

public:
    Tree(const vector<Vertex>& vertices, const vector<GLuint>& indices);
    ~Tree() override = default;

    void draw() const override;
};

#endif
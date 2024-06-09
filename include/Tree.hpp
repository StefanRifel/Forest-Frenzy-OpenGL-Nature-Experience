#ifndef MESH_HH
#define MESH_HH

#include "Mesh.hpp"

class Tree : public Mesh {

public:
    explicit Tree(const vector<Vertex>& vertices);
    ~Tree() override = default;

    void draw() const override;
};

#endif
#ifndef MESH_HH
#define MESH_HH

#include "Mesh.hpp"

class Tree : public Mesh {

public:
    explicit Tree(const std::string& objFile);
    ~Tree() override = default;

    void draw(Camera& camera) const override;
};

#endif
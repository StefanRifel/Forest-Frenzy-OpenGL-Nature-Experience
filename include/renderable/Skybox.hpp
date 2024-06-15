#ifndef SKYBOX_HH
#define SKYBOX_HH

#include "Mesh.hpp"

class Skybox : public Mesh {

public:
    explicit Skybox(const vector<Vertex>& vertices);
    ~Skybox() override = default;

    void draw(Camera& camera) const override;
};

#endif
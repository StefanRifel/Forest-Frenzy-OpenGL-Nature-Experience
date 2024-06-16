#ifndef TERRAIN_HH
#define TERRAIN_HH

#include "Mesh.hpp"

class Terrain : public Mesh {
public:
    Terrain();
    ~Terrain() override = default;

    void draw(Camera& camera) const override;
};

#endif
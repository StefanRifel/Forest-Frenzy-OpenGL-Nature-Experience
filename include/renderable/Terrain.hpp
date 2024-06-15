#ifndef TERRAIN_HH
#define TERRAIN_HH

#include "Mesh.hpp"

class Terrain : public Mesh {
private:
    int numStrips;
    int numTrisPerStrip;

public:
    Terrain(const vector<Vertex>& vertices, const vector<GLuint>& indices, int& numStrips, int& numTrisPerStrip);
    Terrain(const vector<Vertex>& vertices, const vector<GLuint>& indices);
    ~Terrain() override = default;

    void draw(Camera& camera) const override;
};

#endif
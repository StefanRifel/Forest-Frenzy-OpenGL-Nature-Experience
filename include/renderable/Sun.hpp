#ifndef SUN_H
#define SUN_H

#include "Mesh.hpp"

class Sun : public Mesh {

public:
    explicit Sun(const vector<Vertex>& vertices);
    ~Sun() override = default;

    void draw(Camera& camera) const override;
};

#endif

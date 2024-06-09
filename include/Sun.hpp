#ifndef SUN_H
#define SUN_H

#include "Mesh.hpp"

class Sun : public Mesh {

public:
    Sun(const vector<Vertex>& vertices, const vector<GLuint>& indices);
    ~Sun() override = default;

    void draw() const override;
};

#endif

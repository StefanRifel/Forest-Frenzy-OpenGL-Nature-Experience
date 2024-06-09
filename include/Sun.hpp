#ifndef SUN_H
#define SUN_H

#include "Mesh.hpp"

class Sun : public Mesh {

public:
    Sun(const vector<Vertex>& vertices, const vector<GLuint>& indices, const vector<vec3>& normals);
    ~Sun() override = default;

    void draw() const override;
};

#endif

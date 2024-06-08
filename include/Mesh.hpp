#ifndef MESH_HH
#define MESH_HH

#include "RenderableObject.hpp"
#include "../libs/SMath/include/vec3.hpp"

class Mesh : public RenderableObject {
private:
    
public:
    Mesh();
    explicit Mesh(vector<Vertex> vertices);
    Mesh(vector<Vertex> vertices, vector<GLuint> indices);
    virtual ~Mesh() override;
    virtual void draw(Shader shader) const override;
};

#endif
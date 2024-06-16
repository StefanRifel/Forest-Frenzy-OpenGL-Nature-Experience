#ifndef SKYBOX_HH
#define SKYBOX_HH

#include "Mesh.hpp"

class Skybox : public Mesh {

public:
    explicit Skybox(const std::string& objFile);
    ~Skybox() override = default;

    void draw(Camera& camera) const override;

    void setCubeMap();
};

#endif
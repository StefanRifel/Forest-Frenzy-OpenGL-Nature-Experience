#ifndef SUN_H
#define SUN_H

#include "Mesh.hpp"

class Sun : public Mesh {

public:
    explicit Sun(const std::string& objFile);
    ~Sun() override = default;

    void draw(Camera& camera) const override;
};

#endif

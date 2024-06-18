#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <cstring>
#include <cstdio>

#include "Mesh.h"

#include "../../include/loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

class Model {
public:
    vector<Texture> textures_loaded; // stores all the textures loaded so far
    vector<Mesh> meshes;
    vector<Material> materials;
    Shader shader;

    explicit Model(const std::string& objFile);

    void draw(Camera &camera);

private:
    void loadModel(const std::string &objFile);

};

#endif

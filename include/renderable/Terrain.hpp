#ifndef TERRAIN_HH
#define TERRAIN_HH

#include "../../libs/SMath/include/vector.hpp"

#include "Vertex.h"

#include "../Shader.hpp"
#include "../Camera.hpp"

#include "../../include/loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

class Terrain {
private:
    GLuint VAO {0};           ///< Vertex Array Object for the mesh
    GLuint VBO {0};           ///< Vertex Buffer Object for vertex data
    GLuint EBO {0};           ///< Element Buffer Object for index data
    GLuint textureID {0};           ///< Element Buffer Object for index data

    vector<Vertex> vertices;  ///< List of vertices in the mesh
    vector<GLuint> indices;

    Shader shader;

    bool init();
    void setUpTerrain(const std::string& textureFile);

public:
    explicit Terrain(const std::string& textureFile);
    virtual ~Terrain() = default;
    void draw(Camera& camera) const;
};

#endif //TERRAIN_HH

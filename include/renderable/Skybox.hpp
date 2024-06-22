#ifndef SKYBOX_HH
#define SKYBOX_HH

#include "../../libs/SMath/include/vector.hpp"

#include "typs/Vertex.h"

#include "../Shader.hpp"
#include "../Camera.hpp"

#include "../../include/loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

class Skybox {
private:
    GLuint VAO {0};           ///< Vertex Array Object for the mesh
    GLuint VBO {0};           ///< Vertex Buffer Object for vertex data
    GLuint EBO {0};           ///< Element Buffer Object for index data
    GLuint textureID {0};           ///< Element Buffer Object for index data

    vector<vec3> vertices;  ///< List of vertices in the mesh
    vector<GLuint> indices;

    Shader shader;

    bool init(const std::string& objFile);
    void setCubeMap();

public:
    explicit Skybox(const std::string& objFile);
    virtual ~Skybox() = default;
    void draw(Camera& camera) const;
};

#endif //SKYBOX_HH

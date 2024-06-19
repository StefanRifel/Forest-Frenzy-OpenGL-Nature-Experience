#ifndef MOON_HH
#define MOON_HH

#include "../../libs/SMath/include/vector.hpp"

#include "Vertex.h"
#include "Light.h"

#include "../Shader.hpp"
#include "../Camera.hpp"

#include "../../include/loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

class Moon {
private:
    GLuint VAO {0};           ///< Vertex Array Object for the mesh
    GLuint VBO {0};           ///< Vertex Buffer Object for vertex data
    GLuint EBO {0};           ///< Element Buffer Object for index data
    GLuint textureID {0};     ///< Element Buffer Object for index data

    vector<vec3> vertices;  ///< List of vertices in the mesh
    vector<GLuint> indices;
    Light light;

    Shader shader;

    bool init(const std::string& objFile);

public:
    explicit Moon(const std::string& objFile);
    virtual ~Moon() = default;
    void draw(Camera& camera) const;
    Light& getLight();
};

#endif //MOON_HH

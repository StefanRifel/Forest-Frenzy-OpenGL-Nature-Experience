#ifndef RENDERABLE_OBJECT_HH
#define RENDERABLE_OBJECT_HH

#include "Vertex.h"
#include "Material.h"
#include "Face.h"

#include "../Shader.hpp"
#include "../Camera.hpp"

#include "../loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

#include "../Transformation.hpp"

#include "../../libs/SMath/include/vec3.hpp"
#include "../../libs/SMath/include/mat4.hpp"
#include "../../libs/SMath/include/vector.hpp"

/**
 * @brief The Mesh class represents a 3D object that can be rendered in a graphics context.
 *
 * This class encapsulates the necessary data and functionality to render a 3D object using OpenGL.
 * It manages the object's vertex data, indices, color, and the OpenGL buffers needed for rendering.
 *
 * The Mesh class can be subclassed to create more specific types of renderable objects
 * with additional features or behaviors.
 *
 * @note The class assumes that OpenGL context and GLEW initialization have been done prior to creating instances.
 */
class Mesh {

protected:
    bool init();

protected:
    GLuint VAO {0}, VBO {0}, EBO {0}, textureID {0};
    vector<Vertex> vertices;
    Face faces;
    vector<Material> materials;
    Shader shader;

public:
    Mesh();
    explicit Mesh(const std::string& objFile);
    virtual ~Mesh() = default;

    virtual void draw(Camera& camera) const;

    void setTexture(const std::string& textureFile);
}; 

#endif
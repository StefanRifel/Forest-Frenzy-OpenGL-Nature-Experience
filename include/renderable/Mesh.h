#ifndef MESH_HH
#define MESH_HH

#include <string>

#include "../../libs/SMath/include/vector.hpp"

#include "typs/Vertex.h"
#include "typs/Texture.h"
#include "typs/Material.hpp"

#include "../Shader.hpp"
#include "../Camera.hpp"
#include "Drawable.h"


class Mesh {
public:
    vector<Vertex> vertices;  ///< List of vertices in the mesh
    vector<GLuint> indices;   ///< List of indices for indexed drawing
    vector<Texture> textures; ///< List of textures applied to the mesh
    Material material;        ///< Material properties of the mesh
    GLuint VAO {0};
    GLuint VBO {0};         ///< Vertex Buffer Object for vertex data
    GLuint INSTANCE_BUFFER {0};
    GLuint EBO {0};         ///< Element Buffer Object for index data

    mat4 model{1.0f};
    /**
     * @brief Constructs a new Mesh object.
     *
     * @param vertices List of vertices for the mesh
     * @param indices List of indices for indexed drawing
     * @param textures List of textures applied to the mesh
     * @param material Material properties of the mesh
     */
    Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures, Material& material);

    explicit Mesh(const std::string& objFile);
    /**
     * @brief Default destructor.
     */
     ~Mesh();

    /**
     * @brief Draws the mesh using the provided shader and camera.
     *
     * @param shader Shader to use for drawing the mesh
     * @param camera Camera to use for view and projection transformations
     */
    void draw(Shader &shader, Camera &camera) const;

};

#endif // MESH_HH

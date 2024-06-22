#ifndef MESH_HH
#define MESH_HH

#include <string>

#include "../../libs/SMath/include/vector.hpp"

#include "typs/Vertex.h"
#include "typs/Texture.h"
#include "typs/Material.hpp"

#include "../Shader.hpp"
#include "../Camera.hpp"

/**
 * @brief Class representing a mesh in 3D graphics.
 *
 * The Mesh class encapsulates the data and functionality needed to render a 3D mesh,
 * including vertices, indices, textures, materials, and OpenGL buffer objects.
 */
class Mesh {
private:
    GLuint VBO {0}; ///< Vertex Buffer Object for vertex data
    GLuint EBO {0}; ///< Element Buffer Object for index data

    /**
     * @brief Sets up the mesh for rendering by initializing the VAO, VBO, and EBO.
     */
    void setupMesh();

protected:
    vector<Vertex> vertices;  ///< List of vertices in the mesh
    vector<GLuint> indices;   ///< List of indices for indexed drawing
    vector<Texture> textures; ///< List of textures applied to the mesh
    Material material;        ///< Material properties of the mesh
    GLuint VAO {0};           ///< Vertex Array Object for the mesh

public:
    /**
     * @brief Constructs a new Mesh object.
     *
     * @param vertices List of vertices for the mesh
     * @param indices List of indices for indexed drawing
     * @param textures List of textures applied to the mesh
     * @param material Material properties of the mesh
     */
    Mesh(vector<Vertex>& vertices, vector<GLuint>& indices, vector<Texture>& textures, Material& material);

    /**
     * @brief Default destructor.
     */
    ~Mesh() = default;

    /**
     * @brief Draws the mesh using the provided shader and camera.
     *
     * @param shader Shader to use for drawing the mesh
     * @param camera Camera to use for view and projection transformations
     */
    void draw(Shader &shader, Camera &camera) const;
};

#endif // MESH_HH

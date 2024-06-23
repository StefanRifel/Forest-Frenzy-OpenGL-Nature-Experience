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

/**
 * @brief Class representing a mesh in 3D graphics.
 *
 * The Mesh class encapsulates the data and functionality needed to render a 3D mesh,
 * including vertices, indices, textures, materials, and OpenGL buffer objects.
 */
class Mesh : public Drawable {
private:

    /**
     * @brief Sets up the mesh for rendering by initializing the VAO, VBO, and EBO.
     */
    void setupMesh();

public:
    vector<Texture> textures; ///< List of textures applied to the mesh
    Material material;        ///< Material properties of the mesh
    GLuint VAO {0};
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
    ~Mesh() override = default;

    /**
     * @brief Draws the mesh using the provided shader and camera.
     *
     * @param shader Shader to use for drawing the mesh
     * @param camera Camera to use for view and projection transformations
     */
    void draw(Shader &shader, Camera &camera) const;

    void draw(Camera& camera) const override;
};

#endif // MESH_HH

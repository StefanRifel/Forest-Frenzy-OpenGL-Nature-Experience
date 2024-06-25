#ifndef MODEL_HH
#define MODEL_HH

#include <iostream>
#include <cstring>
#include <cstdio>

#include "Mesh.h"

#include "../../include/loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

/**
 * @brief Class representing a 3D model composed of multiple meshes and materials.
 *
 * The Model class handles the loading, storage, and rendering of a 3D model.
 * It uses multiple meshes, materials, and textures to represent the model's geometry and appearance.
 */
class Model {
public:
    vector<Texture> textures_loaded;     ///< Stores all the textures loaded so far
    vector<Mesh> meshes;                 ///< List of meshes that make up the model
    vector<Material> materials;          ///< List of materials used in the model
    Shader shader;                       ///< Shader program used for rendering the model
    unsigned int amount {0};
    mat4* model_matrices;

    /**
     * @brief Constructs a new Model object and loads the model from an OBJ file.
     *
     * @param objFile Name of the OBJ file to load.
     */
    Model(const std::string& objFile, const std::string& shaderName);
    Model(const std::string& objFile, const std::string& shaderName, unsigned int amount);

    /**
     * @brief Draws the model using the provided camera.
     *
     * @param camera Camera used for rendering the model.
     */
    void draw(Camera& camera);
    void setModelTranslation(const mat4& modelTranslation);



private:
    /**
     * @brief Loads the model from an OBJ file.
     *
     * @param objFile Path to the OBJ file to load.
     */
    void loadModel(const std::string& objFile);
    void setUpTranslations();
};

#endif // MODEL_HH

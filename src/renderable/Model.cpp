#include "../../include/renderable/Model.h"
#include "../../include/RenderSystem.hpp"

Model::Model(const std::string& objFile, const std::string& shaderName) {
    if (!shader.createShader(
            AssetLoader::getShaderPath(shaderName + "_vert.glsl"),
            AssetLoader::getShaderPath(shaderName + "_frag.glsl")
        )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
    }

    loadModel(objFile);
}

Model::Model(const std::string &objFile, const std::string &shaderName, unsigned int amount) : amount {amount} {
    if (!shader.createShader(
            AssetLoader::getShaderPath(shaderName + "_vert.glsl"),
            AssetLoader::getShaderPath(shaderName + "_frag.glsl")
    )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
    }

    model_matrices = new mat4[amount];
    setUpTranslations();

    loadModel(objFile);
}

void Model::draw(Camera& camera) {
    for (auto& mesh : meshes) {
        mesh.draw(shader, camera);
        if(amount != 0) {
            RenderSystem::renderInstancedMesh(mesh, model_matrices, amount);
        } else {
            RenderSystem::renderMesh(mesh);
        }
    }
}

void Model::loadModel(const std::string& objFile) {
    auto start = std::chrono::high_resolution_clock::now();

    // Load material and textures from the OBJ file
    OBJModelLoader::loadMtl(objFile, materials, textures_loaded);
    std::cout << objFile << ": load mtl finished" << std::endl;

    // Load meshes from the OBJ file
    OBJModelLoader::loadObj(objFile, meshes, materials, textures_loaded);
    std::cout << objFile << ": load obj finished" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken to load one model: " << elapsed.count() << " seconds" << std::endl;
}

void Model::setModelTranslation(const mat4& modelTranslation) {
    for (auto& mesh:meshes) {
        mesh.model = modelTranslation;
    }
}

void Model::setUpTranslations() {
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-100.0f, 100.0f); // Distribution for range -512 to 512

    for (int i = 0; i < amount; ++i) {
        mat4 model {1.0f}; // Identity matrix initially
        vec3 translate {dis(gen), 0.2f, dis(gen)}; // Random x and z within range, y set to 0
        model = Transformation::translate(model, translate);
        model_matrices[i] = model; // Assuming model_matrices is a std::vector<mat4> where model matrix for each instance is stored
    }
}

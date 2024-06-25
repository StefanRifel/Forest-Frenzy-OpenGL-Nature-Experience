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

void Model::draw(Camera& camera) {
    for (auto& mesh : meshes) {
        mesh.draw(shader, camera);
        RenderSystem::renderInstancedMesh(mesh);
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

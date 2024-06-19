#include "../../include/renderable/Model.h"

Model::Model(const std::string &objFile) {
    if (!shader.createShader(
            AssetLoader::getShaderPath("brass_goblets_vert.glsl"),
            AssetLoader::getShaderPath("brass_goblets_frag.glsl")
        )) {
        std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
    }
    loadModel(objFile);
}

void Model::draw(Camera &camera) {
    for (const auto &mesh : meshes) {
        mesh.Draw(shader, camera);
    }
}

void Model::loadModel(const std::string &objFile) {
    auto start = std::chrono::high_resolution_clock::now();

    OBJModelLoader::loadMtl(objFile, materials, textures_loaded);
    std::cout << objFile << ": load mtl finished" << std::endl;
    OBJModelLoader::loadObj(objFile, meshes, materials, textures_loaded);
    std::cout << objFile << ": load obj finished" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken to load one model: " << elapsed.count() << " seconds" << std::endl;
}

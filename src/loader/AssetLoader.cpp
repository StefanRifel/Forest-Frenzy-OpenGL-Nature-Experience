#include "../../include/loader/AssetLoader.hpp"

const std::string AssetLoader::assetsBasePath = "../assets";
const std::string AssetLoader::shaderBasePath = "../shaders";

std::string AssetLoader::getTexturePath(const std::string& filename) {
    return searchForFile(assetsBasePath + "/textures", filename);
}

std::string AssetLoader::getShaderPath(const std::string& filename) {
    return searchForFile(shaderBasePath , filename);
}

std::string AssetLoader::getModelPath(const std::string& filename) {
    return searchForFile(assetsBasePath + "/models", filename);
}

std::string AssetLoader::searchForFile(const std::string& directory, const std::string& filename) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().filename() == filename) {
            return entry.path().string();
        }
    }

    std::cerr << "Error: File '" << filename << "' not found in directory '" << directory << "'." << std::endl;
    return "";
}
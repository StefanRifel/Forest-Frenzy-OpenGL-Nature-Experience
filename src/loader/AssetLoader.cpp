#include "../../include/loader/AssetLoader.hpp"

const std::string AssetLoader::assetsBasePath = "../assets";
const std::string AssetLoader::shaderBasePath = "../shaders";

/**
 * @brief Class provides utility functions to locate files within specified directories, particularly for assets and shaders
 */

std::string AssetLoader::getAssetPath(const std::string& filename) {
    assert(!filename.empty() && "Filename must not be empty.");
    return searchForFile(assetsBasePath, filename);
}

std::string AssetLoader::getShaderPath(const std::string& filename) {
    assert(!filename.empty() && "Filename must not be empty.");
    return searchForFile(shaderBasePath, filename);
}

std::string AssetLoader::searchForFile(const std::string& directory, const std::string& filename) {
    assert(!directory.empty() && "Directory path must not be empty.");
    assert(!filename.empty() && "Filename must not be empty.");
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().filename() == filename) {
            return entry.path().string();
        }
    }

    std::cerr << "Error: File '" << filename << "' not found in directory '" << directory << "'." << std::endl;
    return "";
}
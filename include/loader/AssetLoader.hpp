#ifndef ASSET_LOADER_HH
#define ASSET_LOADER_HH

#include <string>
#include <iostream>
#include <filesystem>
#include <cassert>

/**
 * @brief Class responsible for loading asset paths and shader paths.
 *
 * The AssetLoader class provides static methods to retrieve paths for assets and shaders.
 * It also contains methods to search for files within specified directories.
 */
class AssetLoader {
public:
    /**
     * @brief Retrieves the full path for a given asset file.
     *
     * @param filename The name of the asset file.
     * @return The full path to the asset file as a string.
     */
    static std::string getAssetPath(const std::string& filename);

    /**
     * @brief Retrieves the full path for a given shader file.
     *
     * @param filename The name of the shader file.
     * @return The full path to the shader file as a string.
     */
    static std::string getShaderPath(const std::string& filename);

private:
    static const std::string assetsBasePath; ///< Base path for asset files
    static const std::string shaderBasePath; ///< Base path for shader files

    /**
     * @brief Searches for a file within a given directory.
     *
     * @param directory The directory to search within.
     * @param filename The name of the file to search for.
     * @return The full path to the file if found, otherwise an empty string.
     */
    static std::string searchForFile(const std::string& directory, const std::string& filename);
};

#endif // ASSET_LOADER_HH

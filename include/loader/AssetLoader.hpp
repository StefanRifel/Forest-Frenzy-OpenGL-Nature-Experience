#ifndef ASSET_LOADER_HH
#define ASSET_LOADER_HH

#include <string>
#include <iostream>
#include <filesystem>

class AssetLoader {
public:
    static std::string getAssetPath(const std::string& filename);
    static std::string getShaderPath(const std::string& filename);

private:
    static const std::string assetsBasePath;
    static const std::string shaderBasePath;

    static std::string searchForFile(const std::string& directory, const std::string& filename);
};

#endif

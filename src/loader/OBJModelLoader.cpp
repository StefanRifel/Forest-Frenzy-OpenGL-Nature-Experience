#include "../../include/OBJModelLoader.hpp"

/**
 * @brief Loads a 3D model from a file in the OBJ format.
 *
 * This function reads a 3D model file specified by the given path. It parses the file to extract vertex positions,
 * vertex normals, and face indices. The parsed data is stored in the provided output vectors for vertices and indices.
 *
 * @param path The file path to the model file to be loaded.
 * @param outVertices A reference to a vector that will store the loaded vertex data.
 * @param outIndices A reference to a vector that will store the loaded face indices.
 * @return true if the model was successfully loaded, false otherwise.
 */
bool OBJModelLoader::load(const char* path, vector<Vertex>& outVertices, vector<GLuint>& outIndices) {
    std::ifstream modelFile {path};
    if(!modelFile.is_open()) {
        std::cerr << "ERROR::MODEL_LOADER::FAILED_TO_OPEN_FILE" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(modelFile, line)) {
        std::istringstream iss {line};
        std::string token;
        iss >> token;

        int index = 0;
        if (token == "v") {
            Vertex vertex;
            iss >> vertex.position.x() >> vertex.position.y() >> vertex.position.z();
            outVertices.push_back(vertex);
        } else if (token == "vn") {
            //iss >> outVertices.at(index).normals.x() >> outVertices.at(index).normals.y() >> outVertices.at(index).normals.z();
            //++index;
        } else if (token == "f") {
            std::string indices;
            while (iss >> indices) {
                std::istringstream viss(indices);
                std::string indexStr;
                getline(viss, indexStr, '/');
                index = std::stoi(indexStr) - 1; // -1 because indices in obj files starts at 1
                outIndices.push_back(index);
            }
        }
    }
    modelFile.close();
    return true;
}
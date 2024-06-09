#include <cstring>
#include "../../include/loader/OBJModelLoader.hpp"

/**
 * @brief Loads a 3D model from a file in the OBJ format.
 *
 * This function reads a 3D model file specified by the given path. It parses the file to extract vertex positions,
 * vertex normals, and face indices. The parsed data is stored in the provided output vectors for vertices and indices.
 *
 * @param path The file path to the model file to be loaded.
 * @param outVertices A reference to a vector that will store the loaded vertex data.
 * @param outIndices A reference to a vector that will store the loaded face indices.
 * @param outNormals A reference to a vector that will store the loaded normals for a vertex.
 * @return true if the model was successfully loaded, false otherwise.
 */
bool OBJModelLoader::load(const char* path, vector<Vertex>& outVertices) {
    vector<GLuint> vertexIndices, normalIndices;
    vector<vec3> tempVertices, tempNormals;

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

        if (token == "v") {
            vec3 vertex;
            iss >> vertex.x() >> vertex.y() >> vertex.z();
            tempVertices.push_back(vertex);
        } else if (token == "vn") {
            vec3 normal;
            iss >> normal.x() >> normal.y() >> normal.z();
            tempNormals.push_back(normal);
        } else if (token == "f") {
            std::string indices;
            while (iss >> indices) {
                std::istringstream viss(indices);
                std::string indexStr;
                // vertex
                getline(viss, indexStr, '/');
                vertexIndices.push_back(std::stoi(indexStr) - 1); // -1 because indices in obj files starts at 1

                // texture
                getline(viss, indexStr, '/');

                // normals
                getline(viss, indexStr, '/');
                normalIndices.push_back(std::stoi(indexStr) - 1);
            }
        }
    }
    modelFile.close();

    for(size_t i = 0; i < vertexIndices.size(); i++){
        Vertex v;
        v.position = tempVertices.at(vertexIndices.at(i));
        v.normal = tempNormals.at(normalIndices.at(i));
        outVertices.push_back(v);
    }

    return true;
}
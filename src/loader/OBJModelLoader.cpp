#include "../../include/loader/OBJModelLoader.hpp"

/**
 * @brief Loads a 3D model from a file in the OBJ format.
 *
 * This function reads a 3D model file specified by the given path. It parses the file to extract vertex positions,
 * vertex normals, and face indices. The parsed data is stored in the provided output vectors for vertices and indices.
 *
 * @param path The file path to the model file to be loaded.
 * @param outVertices A reference to a vector that will store the loaded vertex data (vertices, normals, textures).
 * @return true if the model was successfully loaded, false otherwise.
 */


void OBJModelLoader::loadMtl(const std::string& mtlPath, vector<Material>& materials) {
    std::ifstream mtlFile {mtlPath};

    std::string line;
    int index = 0;

    while (std::getline(mtlFile, line)) {
        std::istringstream iss {line};
        std::string prefix;
        iss >> prefix;

        if(prefix == "newmtl") {
            Material material;
            iss >> material.mtlName;
            materials.push_back(material);
            index = materials.size() - 1;
        } else if (prefix == "ke") {
            iss >> materials.at(index).emissive.r() >> materials.at(index).emissive.g() >> materials.at(index).emissive.b();
        } else if (prefix == "Ka") {
            iss >> materials.at(index).ambient.r() >> materials.at(index).ambient.g() >> materials.at(index).ambient.b();
        } else if (prefix == "Kd") {
            iss >> materials.at(index).diffuse.r() >> materials.at(index).diffuse.g() >> materials.at(index).diffuse.b();
        } else if (prefix == "Ks") {
            iss >> materials.at(index).specular.r() >> materials.at(index).specular.g() >> materials.at(index).specular.b();
        } else if (prefix == "Ns") {
            iss >> materials.at(index).shininess;
        } else if (prefix == "Ni") {
            iss >> materials.at(index).density;
        } else if (prefix == "d") {
            iss >> materials.at(index).dissolve;
        } else if (prefix == "illum") {
            iss >> materials.at(index).illumination;
        }

    }
}

bool OBJModelLoader::loadObj(const std::string& objFile, vector<Vertex>& outVertices, Face& faces, vector<Material>& materials) {
    std::ifstream modelFile {AssetLoader::getModelPath(objFile)};
    if(!modelFile.is_open()) {
        std::cerr << "ERROR::OBJ_MODEL_LOADER::LOAD_OBJ::FAILED_TO_OPEN_FILE" << std::endl;
        return false;
    }

    vector<vec3> tempVertices, tempNormals;
    vector<vec2> tempTextures;

    std::string line;
    while (std::getline(modelFile, line)) {
        std::istringstream iss{line};
        std::string prefix;
        iss >> prefix;

        if (prefix == "mtllib") {
            std::string mtlFile;
            iss >> mtlFile;
            loadMtl(AssetLoader::getModelPath(mtlFile), materials);
        } else if (prefix == "v") {
            vec3 vertex;
            iss >> vertex.x() >> vertex.y() >> vertex.z();
            tempVertices.push_back(vertex);
        } else if (prefix == "vn") {
            vec3 normal;
            iss >> normal.x() >> normal.y() >> normal.z();
            tempNormals.push_back(normal);
        } else if (prefix == "vt") {
            vec2 texture;
            iss >> texture.x() >> texture.y();
            tempTextures.push_back(texture);
        } else if (prefix == "f") {
            char slash;
            int v, t, n;
            while (iss >> v >> slash >> t >> slash >> n) {
                // Assuming the indices are 1-based and need to be adjusted to 0-based
                faces.vertexIndices.push_back(v - 1);
                faces.textureIndices.push_back(t - 1);
                faces.normalIndices.push_back(n - 1);
            }
        }
    }

    modelFile.close();

    for(size_t i = 0; i < faces.vertexIndices.size(); i++){
        Vertex v;
        v.position = tempVertices.at(faces.vertexIndices.at(i));
        v.normal = tempNormals.at(faces.normalIndices.at(i));
        v.texture = tempTextures.at(faces.textureIndices.at(i));
        outVertices.push_back(v);
    }

    return true;
}

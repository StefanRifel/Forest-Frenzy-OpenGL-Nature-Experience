#include "../../include/loader/OBJModelLoader.hpp"

unsigned int OBJModelLoader::LAST_VERTX_INDEX = 0;
unsigned int OBJModelLoader::LAST_NORMAL_INDEX = 0;
unsigned int OBJModelLoader::LAST_TEXTURE_INDEX = 0;

void OBJModelLoader::loadMtl(const std::string& mtlFile, vector<Material>& outMaterials) {

    std::ifstream file{AssetLoader::getAssetPath(mtlFile + ".mtl")};

    if (!file.is_open()) {
        std::cerr << "Unable to open MTL file: " << mtlFile << std::endl;
    }

    std::string line;
    int index = 0;
    while (std::getline(file, line)) {
        std::istringstream iss{line};
        std::string prefix;
        iss >> prefix;

        if (prefix == "newmtl") {
            Material material;
            iss >> material.mtlName;
            outMaterials.push_back(material);
            index = outMaterials.size() - 1;
        } else if (prefix == "Ka") {
            iss >> outMaterials.at(index).ambient.r() >> outMaterials.at(index).ambient.g() >> outMaterials.at(index).ambient.b();
        } else if (prefix == "Kd") {
            iss >> outMaterials.at(index).diffuse.r() >> outMaterials.at(index).diffuse.g() >> outMaterials.at(index).diffuse.b();
        } else if (prefix == "Ks") {
            iss >> outMaterials.at(index).specular.r() >> outMaterials.at(index).specular.g() >> outMaterials.at(index).specular.b();
        } else if (prefix == "Ke") {
            iss >> outMaterials.at(index).emissive.r() >> outMaterials.at(index).emissive.g() >> outMaterials.at(index).emissive.b();
        } else if (prefix == "Ns") {
            iss >> outMaterials.at(index).shininess;
        } else if (prefix == "Ni") {
            iss >> outMaterials.at(index).density;
        } else if (prefix == "d") {
            iss >> outMaterials.at(index).dissolve;
        } else if (prefix == "illum") {
            iss >> outMaterials.at(index).illumination;
        } else if (prefix == "map_Kd") {
            iss >> outMaterials.at(index).diffuse_map;
        } else if (prefix == "map_Ns") {
            iss >> outMaterials.at(index).shininess_map;
        } else if (prefix == "map_refl") {
            iss >> outMaterials.at(index).reflect_map;
        } else if (prefix == "map_Bump") {
            std::string bumpFlag;
            iss >> bumpFlag; // read "-bm"
            if (bumpFlag == "-bm") {
                float bm;
                iss >> bm; // read bump multiplier (usually 1.0)
                iss >> outMaterials.at(index).normal_map;
                outMaterials.at(index).bumpMultiplier = bm; // store the bump multiplier if needed
            }
        }
    }
    file.close();
}

void OBJModelLoader::loadObj(const std::string& objFile, vector<Mesh>& outMeshes, vector<Material>& outMaterials) {
    OBJModelLoader::LAST_VERTX_INDEX = 0;
    OBJModelLoader::LAST_NORMAL_INDEX = 0;
    OBJModelLoader::LAST_TEXTURE_INDEX = 0;

    vector<std::string> dividedObj;
    divideObj(AssetLoader::getAssetPath(objFile + ".obj"), dividedObj);

    for (const auto& meshInput : dividedObj) {
        outMeshes.push_back(createMesh(meshInput, outMaterials));
    }
}

Mesh OBJModelLoader::createMesh(const std::string& meshInput, vector<Material>& outMaterials) {
    vector<vec3> tempVertices, tempNormals;
    vector<vec2> tempTextures;
    Face faces;

    std::istringstream issMesh{meshInput};
    std::string line;
    std::string usemtl;

    while (std::getline(issMesh, line)) {
        std::istringstream iss{line};
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
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
        } else if (prefix == "usemtl") {
            iss >> usemtl;
        } else if (prefix == "f") {
            char slash;
            int v, t, n;
            while (iss >> v >> slash >> t >> slash >> n) {
                faces.vertexIndices.push_back(v - 1 - OBJModelLoader::LAST_VERTX_INDEX);
                faces.normalIndices.push_back(n - 1 - OBJModelLoader::LAST_NORMAL_INDEX);
                faces.textureIndices.push_back(t - 1 - OBJModelLoader::LAST_TEXTURE_INDEX);
            }
        }
    }

    OBJModelLoader::LAST_VERTX_INDEX += tempVertices.size();
    OBJModelLoader::LAST_NORMAL_INDEX += tempNormals.size();
    OBJModelLoader:: LAST_TEXTURE_INDEX += tempTextures.size();

    vector<Vertex> vertices;
    for (size_t i = 0; i < faces.vertexIndices.size(); ++i) {
        Vertex v;
        v.Position = tempVertices.at(faces.vertexIndices.at(i));
        v.Normal = tempNormals.at(faces.normalIndices.at(i));
        v.TexCoords = tempTextures.at(faces.textureIndices.at(i));
        vertices.push_back(v);
    }

    Material material;
    for (const auto& search: outMaterials) {
        if (search.mtlName == usemtl) {
            material = search;
        }
    }

    vector<Texture> textures = TextureLoader::loadMaterialTextures(material);

    return Mesh{vertices, faces.vertexIndices, textures, material};
}

void OBJModelLoader::divideObj(const std::string &filePath, vector<std::string> &outMeshes) {
    FILE *file = fopen(filePath.c_str(), "r");
    if (!file) {
        std::cerr << "ERROR::MODEL::PROCESS_OBJ_FILE::FAILED_TO_OPEN_FILE::" << filePath << std::endl;
        return;
    }

    constexpr size_t MAX_LINE_LENGTH = 256;
    char line[MAX_LINE_LENGTH];
    std::string currentConstruct;
    bool insideConstruct = false;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "o ", 2) == 0) {
            if (insideConstruct) {
                outMeshes.push_back(std::move(currentConstruct));
                currentConstruct.clear();
            }
            insideConstruct = true;
        }

        if (insideConstruct) {
            currentConstruct += line;
        }
    }

    if (!currentConstruct.empty()) {
        outMeshes.push_back(std::move(currentConstruct));
    }

    fclose(file);
}

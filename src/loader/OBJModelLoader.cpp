#include "../../include/loader/OBJModelLoader.hpp"

unsigned int OBJModelLoader::LAST_VERTX_INDEX = 0;
unsigned int OBJModelLoader::LAST_NORMAL_INDEX = 0;
unsigned int OBJModelLoader::LAST_TEXTURE_INDEX = 0;

void OBJModelLoader::loadMtl(const std::string& mtlFile, vector<Material>& outMaterials, vector<Texture>& outTextures) {

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
        } else if (prefix == "map_Ka") {
            iss >> outMaterials.at(index).ambient_map;
        } else if (prefix == "map_Pr") {
            iss >> outMaterials.at(index).roughness_map;
        } else if (prefix == "map_Pm") {
            iss >> outMaterials.at(index).metalness_map;
        } else if (prefix == "map_bump") {
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

    for (auto& material: outMaterials) {
        vector<Texture> loadMaterialTextures = TextureLoader::loadMaterialTextures(material);
        for (auto& tex: loadMaterialTextures) {
            outTextures.push_back(tex);
        }
    }
}

void OBJModelLoader::loadObj(const std::string& objFile, vector<Mesh>& outMeshes, vector<Material>& outMaterials, vector<Texture>& outTextures) {
    OBJModelLoader::LAST_VERTX_INDEX = 0;
    OBJModelLoader::LAST_NORMAL_INDEX = 0;
    OBJModelLoader::LAST_TEXTURE_INDEX = 0;

    vector<std::string> dividedObj;
    divideObj(AssetLoader::getAssetPath(objFile + ".obj"), dividedObj);

    for (const auto& meshInput : dividedObj) {
        outMeshes.push_back(createMesh(meshInput, outMaterials, outTextures));
    }
}

Mesh OBJModelLoader::createMesh(const std::string& meshInput, vector<Material>& outMaterials, vector<Texture>& outTextures) {
    vector<vec3> tempVertices, tempNormals;
    vector<vec2> tempTextures;
    Face faces;

    std::istringstream issMesh{meshInput};
    std::string line;
    std::string usemtl;

    while (std::getline(issMesh, line)) {
        if (line.empty()) continue;
        char prefix = line[0];

        switch (prefix) {
            case 'v': {
                if (line[1] == ' ') {
                    vec3 vertex;
                    sscanf(line.c_str(), "v %f %f %f", &vertex.x(), &vertex.y(), &vertex.z());
                    tempVertices.push_back(vertex);
                } else if (line[1] == 'n') {
                    vec3 normal;
                    sscanf(line.c_str(), "vn %f %f %f", &normal.x(), &normal.y(), &normal.z());
                    tempNormals.push_back(normal);
                } else if (line[1] == 't') {
                    vec2 texture;
                    sscanf(line.c_str(), "vt %f %f", &texture.x(), &texture.y());
                    tempTextures.push_back(texture);
                }
                break;
            }
            case 'u': {
                char mtl[64];
                sscanf(line.c_str(), "usemtl %s", mtl);
                usemtl = mtl;
                break;
            }
            case 'f': {
                int v[3], t[3], n[3];
                if (sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                           &v[0], &t[0], &n[0],
                           &v[1], &t[1], &n[1],
                           &v[2], &t[2], &n[2]) == 9) {
                    for (int i = 0; i < 3; i++) {
                        faces.vertexIndices.push_back(v[i] - 1 - OBJModelLoader::LAST_VERTX_INDEX);
                        faces.normalIndices.push_back(n[i] - 1 - OBJModelLoader::LAST_NORMAL_INDEX);
                        faces.textureIndices.push_back(t[i] - 1 - OBJModelLoader::LAST_TEXTURE_INDEX);
                    }
                }
                break;
            }
            default:
                break;
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
            break;
        }
    }

    vector<Texture> textures;

    for (auto a:outTextures) {
        if(material.mtlName == a.usemtlName) {
            Texture t;
            t.usemtlName = a.usemtlName;
            t.type = a.type;
            t.id = a.id;
            textures.push_back(t);
        }
    }

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

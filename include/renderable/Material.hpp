#ifndef MATERIAL_HH
#define MATERIAL_HH

#include "../../libs/SMath/include/vec3.hpp"

/**
 * @brief Struct representing a material with various properties.
 */
typedef struct {
    char mtlName[64] = {};                      ///< Name of the material

    vec3 emissive{0.0f, 0.0f, 0.0f};            ///< Ke: Emissive color of the material
    vec3 ambient{0.0f, 0.0f, 0.0f};             ///< Ka: Ambient color of the material
    vec3 diffuse{0.0f, 0.0f, 0.0f};             ///< Kd: Diffuse color of the material
    vec3 specular{0.0f, 0.0f, 0.0f};            ///< Ks: Specular color of the material

    float shininess = 0.0f;                    ///< Ns: Shininess of the material
    float density = 0.0f;                      ///< Ni: Refractive index of the material
    float dissolve = 0.0f;                     ///< d: Dissolve (transparency) of the material

    float illumination = 0.0f;                 ///< illum: Illumination model of the material
    float bumpMultiplier{0.0f};                ///< Bump map intensity multiplier

    char normal_map[64] = {};                  ///< map_bump: normal map (height or bump map)
    char ambient_map[64] = {};                 ///< map_Ka: Ambient occlusion map
    char diffuse_map[64] = {};                 ///< map_Kd: Diffuse map
    char metalness_map[64] = {};               ///< map_Pm: Metalness map (custom)
    char roughness_map[64] = {};               ///< map_Pr: Roughness map (custom)
} Material;

#endif // MATERIAL_HH

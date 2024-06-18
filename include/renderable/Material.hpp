#ifndef MATERIAL_HH
#define MATERIAL_HH

#include "../../libs/SMath/include/vec3.hpp"

typedef struct {
    char mtlName[64] = {};
    vec3 emissive{0.0f, 0.0f, 0.0f};    ///< Ke
    vec3 ambient{0.0f, 0.0f, 0.0f};     ///< Ka
    vec3 diffuse{0.0f, 0.0f, 0.0f};     ///< Kd
    char diffuse_map[64] = {};                   ///< map_Kd
    vec3 specular{0.0f, 0.0f, 0.0f};    ///< Ks
    float shininess = 0.0f;                      ///< Ns
    char shininess_map[64] = {};                 ///< map_Ns

    float density = 0.0f;                        ///< Ni
    float dissolve = 0.0f;                       ///< d

    float illumination = 0.0f;                   ///< illum

    char reflect_map[64] = {};                   ///< map_refl
    char normal_map[64] = {};                      ///< map_Bump
    float bumpMultiplier{0.0f};
} Material;

#endif
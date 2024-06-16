#ifndef MATERIAL_HH
#define MATERIAL_HH

#include "../../libs/SMath/include/vec3.hpp"

typedef struct {
    char mtlName[64];
    vec3 emissive;    ///< Ke
    vec3 ambient;     ///< Ka
    vec3 diffuse;     ///< Kd
    vec3 specular;    ///< Ks
    float shininess;  ///< Ns

    float density;    ///< Ni
    float dissolve;   ///< d

    float illumination; ///< illum
} Material;

enum MaterialType {
    MATERIAL_GOLD,
    MATERIAL_SILVER,
    MATERIAL_BRONZE,
    MATERIAL_RUBY,
    MATERIAL_JADE,
    MATERIAL_BLACK_PLASTIC,
    MATERIAL_COUNT
};

const Material MATERIALS[MATERIAL_COUNT] = {
        {
                "Gold",
                vec3(0.0f, 0.0f, 0.0f), // emissive
                vec3(0.24725f, 0.1995f, 0.0745f), // ambient
                vec3(0.75164f, 0.60648f, 0.22648f), // diffuse
                vec3(0.628281f, 0.555802f, 0.366065f), // specular
                51.2f, // shininess
                1.0f, // density
                1.0f, // dissolve
                2.0f // illumination
        },
        {
                "Silver",
                vec3(0.0f, 0.0f, 0.0f), // emissive
                vec3(0.19225f, 0.19225f, 0.19225f), // ambient
                vec3(0.50754f, 0.50754f, 0.50754f), // diffuse
                vec3(0.508273f, 0.508273f, 0.508273f), // specular
                51.2f, // shininess
                1.0f, // density
                1.0f, // dissolve
                2.0f // illumination
        },
        {
                "Bronze",
                vec3(0.0f, 0.0f, 0.0f), // emissive
                vec3(0.2125f, 0.1275f, 0.054f), // ambient
                vec3(0.714f, 0.4284f, 0.18144f), // diffuse
                vec3(0.393548f, 0.271906f, 0.166721f), // specular
                25.6f, // shininess
                1.0f, // density
                1.0f, // dissolve
                2.0f // illumination
        },
        {
                "Ruby",
                vec3(0.0f, 0.0f, 0.0f), // emissive
                vec3(0.1745f, 0.01175f, 0.01175f), // ambient
                vec3(0.61424f, 0.04136f, 0.04136f), // diffuse
                vec3(0.727811f, 0.626959f, 0.626959f), // specular
                76.8f, // shininess
                1.0f, // density
                0.55f, // dissolve
                2.0f // illumination
        },
        {
                "Jade",
                vec3(0.0f, 0.0f, 0.0f), // emissive
                vec3(0.135f, 0.2225f, 0.1575f), // ambient
                vec3(0.54f, 0.89f, 0.63f), // diffuse
                vec3(0.316228f, 0.316228f, 0.316228f), // specular
                12.8f, // shininess
                1.0f, // density
                0.95f, // dissolve
                2.0f // illumination
        },
        {
                "Black Plastic",
                vec3(0.0f, 0.0f, 0.0f), // emissive
                vec3(0.0f, 0.0f, 0.0f), // ambient
                vec3(0.01f, 0.01f, 0.01f), // diffuse
                vec3(0.50f, 0.50f, 0.50f), // specular
                32.0f, // shininess
                1.0f, // density
                1.0f, // dissolve
                2.0f // illumination
        }
};

#endif
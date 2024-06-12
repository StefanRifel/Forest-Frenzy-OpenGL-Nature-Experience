#ifndef MATERIAL_HH
#define MATERIAL_HH

#include "../../libs/SMath/include/vec3.hpp"

typedef struct {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
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

const Material materials[MATERIAL_COUNT] = {
    {
            vec3(0.24725f, 0.1995f, 0.0745f),
            vec3(0.75164f, 0.60648f, 0.22648f),
            vec3(0.628281f, 0.555802f, 0.366065f),
            51.2f
    },
    {
            vec3(0.19225f, 0.19225f, 0.19225f),
            vec3(0.50754f, 0.50754f, 0.50754f),
            vec3(0.508273f, 0.508273f, 0.508273f),
            51.2f
    },
    {
            vec3(0.2125f, 0.1275f, 0.054f),
            vec3(0.714f, 0.4284f, 0.18144f),
            vec3(0.393548f, 0.271906f, 0.166721f),
            25.6f
    },
    {
            vec3(0.1745f, 0.01175f, 0.01175f),
            vec3(0.61424f, 0.04136f, 0.04136f),
            vec3(0.727811f, 0.626959f, 0.626959f),
            76.8f
    },
    {
            vec3(0.135f, 0.2225f, 0.1575f),
            vec3(0.54f, 0.89f, 0.63f),
            vec3(0.316228f, 0.316228f, 0.316228f),
            12.8f
    },
    {
            vec3(0.0f, 0.0f, 0.0f),
            vec3(0.01f, 0.01f, 0.01f),
            vec3(0.50f, 0.50f, 0.50f),
            32.0f
    }
};

#endif
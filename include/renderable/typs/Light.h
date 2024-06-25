#ifndef LIGHT_H
#define LIGHT_H

#include "../../../libs/SMath/include/vec3.hpp"

/**
 * @brief Struct describe the properties of a light source.
 */
typedef struct {
    vec3 color;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} Light;

#endif //LIGHT_H

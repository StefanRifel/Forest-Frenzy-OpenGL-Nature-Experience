#ifndef VERTEX_HH
#define VERTEX_HH

#include "../../libs/SMath/include/vec3.hpp"
#include "../../libs/SMath/include/vec2.hpp"

typedef struct {
    vec3 position;
    vec3 normal;
    vec2 texture;
} Vertex;

#endif
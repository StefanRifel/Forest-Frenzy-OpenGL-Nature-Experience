#ifndef VERTEX_HH
#define VERTEX_HH

#include "../../libs/SMath/include/vec3.hpp"
#include "../../libs/SMath/include/vec2.hpp"

typedef struct {
    vec3 Position;    // position
    vec3 Normal;      // normal
    vec2 TexCoords;   // texCoords
} Vertex;

#endif

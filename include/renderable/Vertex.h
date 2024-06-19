#ifndef VERTEX_HH
#define VERTEX_HH

#include "../../libs/SMath/include/vec3.hpp"
#include "../../libs/SMath/include/vec2.hpp"

/**
 * @brief Struct representing a vertex with position, normal, and texture coordinates.
 */
typedef struct {
    vec3 position;    ///< position of the vertex
    vec3 normal;      ///< normal vector associated with the vertex
    vec2 texCoords;   ///< Texture coordinates of the vertex
} Vertex;

#endif // VERTEX_HH


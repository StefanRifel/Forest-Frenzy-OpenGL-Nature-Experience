#ifndef VERTEX_HH
#define VERTEX_HH

#include "../libs/SMath/include/vec3.hpp"
#include <vector>
#include <GLFW/glfw3.h>

struct Vertex {
    vec3 position;
    vec3 normals;
};

#endif
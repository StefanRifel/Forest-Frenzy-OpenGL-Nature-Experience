#ifndef RENDERABLE_HH
#define RENDERABLE_HH

#include "../../../libs/SMath/include/vec3.hpp"
#include "../../../include/Vertex.hpp"

namespace ecs {
    
    struct Renderable {
        GLuint VAO, VBO, EBO;
        vec3 color;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
    };
}

#endif
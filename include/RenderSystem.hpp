#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Shader.hpp"
#include "renderable/Model.h"
#include "../libs/SMath/include/vec4.hpp"
#include <cassert>

/**
 * @brief Header file defines a RenderSystem class that provides static methods for creating model matrices and rendering meshes in a 3D graphics application, including support for instanced rendering. 
 */

class RenderSystem {
public:
    static unsigned int AMOUNT;
    static void createModelMatrices();
    static void renderMesh(Mesh& mesh);
    static void renderInstancedMesh(Mesh& mesh, mat4* model_matrices, unsigned int amount);
};


#endif //RENDER_SYSTEM_H

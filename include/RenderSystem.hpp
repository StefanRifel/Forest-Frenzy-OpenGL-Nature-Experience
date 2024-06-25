#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Shader.hpp"
#include "renderable/Model.h"
#include "../libs/SMath/include/vec4.hpp"
#include <cassert>

class RenderSystem {
public:
    static unsigned int AMOUNT;
    static void createModelMatrices();
    static void renderMesh(Mesh& mesh);
    static void renderInstancedMesh(Mesh& mesh, mat4* model_matrices, unsigned int amount);
};


#endif //RENDER_SYSTEM_H

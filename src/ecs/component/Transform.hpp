#ifndef TRANSFORM_HH
#define TRANSFORM_HH

#include "../../../libs/SMath/include/vec3.hpp"

namespace ecs {
    
    struct Transform {
        vec3 position;
        vec3 rotation;
        vec3 scale;
    };
}

#endif
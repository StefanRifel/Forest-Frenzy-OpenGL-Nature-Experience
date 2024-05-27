#ifndef CAMERA_HH
#define CAMERA_HH

#include "../../../libs/SMath/include/vec3.hpp"

namespace ecs {

    struct Camera {
        vec3 cameraPos;
        vec3 cameraFront;
        vec3 cameraUp;
    };
}

#endif
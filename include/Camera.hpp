#ifndef CAMERA_HH
#define CAMERA_HH

#include "../libs/SMath/include/vec3.hpp"
#include "../libs/SMath/include/mat4.hpp"
#include "Transformation.hpp"

#include "Shader.hpp"

class Camera {

private:
    
public:
    vec3 cameraPos;
    vec3 cameraFront;
    vec3 cameraUp;

    Camera();
    void look(Shader& shader) const;
};

#endif
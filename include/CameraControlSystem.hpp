#ifndef CAMERACONTROLSYSTEM_HH
#define CAMERACONTROLSYSTEM_HH

#include "../libs/SMath/include/vec3.hpp"
#include "../libs/SMath/include/mat4.hpp"
#include "Transformation.hpp"

#include "WindowManager.hpp"
#include "Shader.hpp"

#include "../src/ecs/core/types/System.hpp"

class CameraControlSystem : public ecs::System {

private:
    WindowManager* windowManager;
public:
    CameraControlSystem();
    bool init(WindowManager* windowManager);
    void render(Shader& shader);
};

#endif
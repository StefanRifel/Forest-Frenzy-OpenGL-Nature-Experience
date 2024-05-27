#include "../../../include/CameraControlSystem.hpp"

CameraControlSystem::CameraControlSystem() {
    //this->cameraPos = {0.0f, 0.0f, 3.0f};
    //this->cameraFront = {0.0f, 0.0f, 0.0f};
    //this->cameraUp = {0.0f, 1.0f, 0.0f};
}

bool CameraControlSystem::init(WindowManager* windowManager) {
    this->windowManager = windowManager;


    ecs::Entity entity = windowManager->coordinator.createEntity();
    windowManager->coordinator.addComponent(entity, 
        ecs::Transform{
            .position = vec3(0.0f, 0.0f, 0.0f),
            .rotation = vec3(0.0f, 0.0f, 0.0f),
            .scale = vec3(0.0f, 0.0f, 0.0f)
        }
    );

    windowManager->coordinator.addComponent(entity, 
        ecs::Camera{
            .cameraPos = vec3 {1.0f, 7.0f, 8.0f},
            .cameraFront = vec3 {0.0f, 0.0f, 0.0f},
            .cameraUp = vec3 {0.0f, 1.0f, 0.0f}
        }
    );
    return true;
}

void CameraControlSystem::render(Shader& shader) {
    for (auto const& entity : entities) {
        auto e = windowManager->coordinator.getComponent<ecs::Camera>(entity);

        // set view matrix in shader
        shader.setView(Transformation::lookAt(e.cameraPos, e.cameraFront, e.cameraUp));

        // set projection matrix in shader
        shader.setProjection(Transformation::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
    }
}
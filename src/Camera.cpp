#include "../include/Camera.hpp"

Camera::Camera() {
    this->cameraPos = {1.0f, 1.0f, 3.0f};
    this->cameraFront = {0.0f, 0.0f, 0.0f};
    this->cameraUp = {0.0f, 1.0f, 0.0f};
}

void Camera::look(Shader& shader) const {

    // set view matrix in shader
    shader.setView(Transformation::lookAt(cameraPos, cameraFront, cameraUp));

    // set projection matrix in shader
    shader.setProjection(Transformation::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
}
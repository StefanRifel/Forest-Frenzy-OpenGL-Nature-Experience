#include "../include/Camera.hpp"

Camera::Camera()
    : movementSpeed {DEFAULT_SPEED}, mouseSensitivity {DEFAULT_SENSITIVITY}, fieldOfView {FOV}, yaw {DEFAULT_YAW}, pitch {DEFAULT_PITCH} {
    this->position = {0.0f, 0.0f, 0.0f};
    this->front = {0.0f, 0.0f, -1.0f};
    this->worldUp = {0.0f, 1.0f, 0.0f};

    updateCameraVectors();
}

void Camera::look() {
    // set view matrix in shader
    vec3 pf = position + front;
    this->view = Transformation::lookAt(position, pf, up);

    // set projection matrix in shader
    this->perspective = Transformation::perspective(fieldOfView, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
}

void Camera::processKeyboard(Camera_Movement direction, float cDeltaTime) {

    float velocity = movementSpeed * cDeltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
}

/**
     * @brief Processes input received from a mouse input system.
     *
     * @param xPos The new X position of the mouse.
     * @param yPos The new Y position of the mouse.
     * @param constrainPitch Whether to constrain the pitch angle to avoid flipping the camera.
 */
void Camera::processMouseMovement(float xPos, float yPos, GLboolean constrainPitch = true) {

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;


    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::zoomWithMouseScroll(float yOffset) {
    fieldOfView -= (float)yOffset;
    if (fieldOfView < 45.0f) {
        fieldOfView = 45.0f;
    }
    if (fieldOfView > 120.0f) {
        fieldOfView = 120.0f;
    }
}

mat4& Camera::getView() {
    return view;
}

const mat4& Camera::getPerspective() const {
    return perspective;
}

const vec3 &Camera::getPosition() const {
    return position;
}

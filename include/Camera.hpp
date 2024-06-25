#ifndef CAMERA_HH
#define CAMERA_HH

#include <cmath>

#include "../libs/SMath/include/vec3.hpp"
#include "../libs/SMath/include/mat4.hpp"
#include "Transformation.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Constants for default camera settings
const float FOV = 60.0f;
const float ASPECT_RATIO = 1024.0f / 768.0f;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 1000.0f;

const float DEFAULT_YAW         = -90.0f;
const float DEFAULT_PITCH       = 0.0f;

// Default movement values
const float DEFAULT_SPEED       =  2.5f;
const float DEFAULT_SENSITIVITY =  0.1f;

/**
     * @class Camera
     * @brief A camera class that processes input and calculates the corresponding Euler Angles, Vectors, and Matrices for use in OpenGL.
     *
     * The Camera class handles all the operations related to the camera's position, orientation, and movement.
     * It processes keyboard and mouse input to update the camera's position and orientation and provides methods to get view and projection matrices for rendering.
     *
     * Here is a simple ASCII representation of the camera setup:
     *
     *       +Y  (up)
     *        |
     *        |
     *        |
     *        O-------> +X (Right)
     *       /
     *      /
     *     v +Z (Forward)
     *
     * The camera looks in the direction of the positive Z-axis by default, and can move and rotate in the 3D space.
 */
class Camera {

private:
    vec3 position;                  ///< Camera position in world space
    vec3 front;                     ///< Camera front direction
    vec3 up;                        ///< Camera up direction
    vec3 right;                     ///< Camera right direction
    vec3 worldUp;                   ///< World's up direction

    mat4 view;
    mat4 perspective;

    // Camera rotation
    float yaw;                      ///< Camera yaw (horizontal rotation)
    float pitch;                    ///< Camera pitch (vertical rotation)

    // Camera options
    float movementSpeed;            ///< Camera movement speed
    float mouseSensitivity;         ///< Mouse sensitivity for looking around
    float fieldOfView;              ///< Field of view for zoom

    float lastX = 1024.0f / 2;      ///< Last X position of the mouse
    float lastY = 768.0f / 2;       ///< Last Y position of the mouse

    void updateCameraVectors() {
        // Calculate the new Front vector
        vec3 newFront;
        newFront.x() = std::cos(Transformation::radiant(yaw)) * std::cos(Transformation::radiant(pitch));
        newFront.y() = std::sin(Transformation::radiant(pitch));
        newFront.z() = std::sin(Transformation::radiant(yaw)) * std::cos(Transformation::radiant(pitch));
        front = Transformation::normalize(newFront);

        right = Transformation::normalize(Transformation::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up    = Transformation::normalize(Transformation::cross(right, front));
    }

public:
    float deltaTime = 0.0f;	        ///< Time between current frame and last frame
    float lastFrame = 0.0f;         ///< Time of the last frame

    Camera();
    void look();

    mat4 &getView();
    const mat4& getPerspective() const;

    const vec3& getPosition() const;
    const vec3& getFront() const;

    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xPos, float yPos, GLboolean constrainPitch);
    void zoomWithMouseScroll(float yOffset);
};

#endif
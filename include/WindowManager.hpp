#ifndef WINDOWManager_HH
#define WINDOWManager_HH

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLContext;
#include "OpenGLContext.hpp"
class GUIContext;
#include "GUIContext.hpp"
class RenderSystem;
#include "RenderSystem.hpp"
class CameraControlSystem;
#include "CameraControlSystem.hpp"
class UIPanel;
#include "UIPanel.hpp"

#include "../src/ecs/core/Coordinator.hpp"
#include "../src/ecs/component/Transform.hpp"
#include "../src/ecs/component/Renderable.hpp"
#include "../src/ecs/component/Camera.hpp"

#include "../src/ecs/core/EventManager.hpp"

class WindowManager {
public:
    // GLFWwindow is inizialized in OpenGLContext
    GLFWwindow* window;
    
    std::string programmName;
    GLuint width;
    GLuint height;

    bool isRunning;
    
    Shader shader;

    OpenGLContext* openglContext;
    GUIContext* guiContext;
    UIPanel* uiPanel;

    ecs::Coordinator coordinator;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<CameraControlSystem> cameraControlSystem;

public:
    WindowManager(GLuint width, GLuint height, std::string programmName);
    ~WindowManager();

    void init();
    void render();

    void onResize(GLuint width, GLuint height);
    void onClose();
};

#endif
#ifndef WINDOW_HH
#define WINDOW_HH

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLContext;
#include "OpenGLContext.hpp"
class Scene;
#include "Scene.hpp"

class Window {
public:
    // GLFWwindow is inizialized in OpenGLContext
    GLFWwindow* window;
    
    std::string programmName;
    GLuint width;
    GLuint height;

    bool isRunning;
    
    OpenGLContext* openglContext;
    Scene* scene;

public:
    Window(GLuint width, GLuint height, std::string programmName);
    ~Window();

    void init();
    void render();

    void onResize(GLuint width, GLuint height);
    void onClose();
};

#endif
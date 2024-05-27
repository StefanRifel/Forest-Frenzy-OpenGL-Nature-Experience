#include "../include/OpenGLContext.hpp"

// callback functions

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    auto pWindow = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
    pWindow->onResize(width, height);
}

static void on_window_close_callback(GLFWwindow* window) {
    auto pWindow = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
    pWindow->onClose();
}

// class functions

OpenGLContext::OpenGLContext() {}

OpenGLContext::~OpenGLContext() {
    glfwTerminate();
}

bool OpenGLContext::init(WindowManager* windowManager) {
    // call parent class init
    if(!RenderContext::init(windowManager)) {
        std::cerr << "ERROR::OPENGLCONTEXT::FAILED_TO_INIT_RENDERCONTEXT" << std::endl;
    }

    // inizialize glfw and set version
    if(!glfwInit()) {
        std::cerr << "ERROR::OPENGLCONTEXT::FAILED_TO_GLFW_INIT" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // inizialize GLFWwindow
    windowManager->window = glfwCreateWindow(windowManager->width, windowManager->height, windowManager->programmName.c_str(), NULL, NULL);
    if (!windowManager) {
        std::cerr << "ERROR::OPENGLCONTEXT::FAILED_TO_CREATE_WINDOW" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(windowManager->window, windowManager);
    glfwSetFramebufferSizeCallback(windowManager->window, framebuffer_size_callback);
    glfwSetWindowCloseCallback(windowManager->window, on_window_close_callback);
    glfwMakeContextCurrent(windowManager->window);
    glewInit();

    return true;
}

void OpenGLContext::preRender() {
    glViewport(0,0, windowManager->width, windowManager->height);
    // set default backgroundcolor
    glClearColor(0.08f, 0.06f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::postRender() {
    // check and call events and swap the buffers
    glfwSwapBuffers(windowManager->window);
    glfwPollEvents();
}
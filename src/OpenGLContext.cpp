#include "../include/OpenGLContext.hpp"

// callback functions

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    auto pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    pWindow->onResize(width, height);
}

static void on_window_close_callback(GLFWwindow* window) {
    auto pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    pWindow->onClose();
}

// class functions

OpenGLContext::OpenGLContext() {}

OpenGLContext::~OpenGLContext() {
    glfwTerminate();
}

bool OpenGLContext::init(Window* window) {
    // call parent class init
    if(!RenderContext::init(window)) {
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
    window->window = glfwCreateWindow(window->width, window->height, window->programmName.c_str(), NULL, NULL);
    if (!window) {
        std::cerr << "ERROR::OPENGLCONTEXT::FAILED_TO_CREATE_WINDOW" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(window->window, window);
    glfwSetFramebufferSizeCallback(window->window, framebuffer_size_callback);
    glfwSetWindowCloseCallback(window->window, on_window_close_callback);
    glfwMakeContextCurrent(window->window);
    glewInit();

    return true;
}

void OpenGLContext::preRender() {
    glViewport(0,0, window->width, window->height);
    // set default backgroundcolor
    glClearColor(0.94f, 0.93f, 0.81f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::postRender() {
    // check and call events and swap the buffers
    glfwSwapBuffers(window->window);
    glfwPollEvents();
}
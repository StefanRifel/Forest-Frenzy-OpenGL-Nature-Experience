#include "../../include/context/OpenGLContext.hpp"

// Callback functions
static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    auto pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    pWindow->onResize(width, height);
}

static void on_window_close_callback(GLFWwindow* window) {
    auto pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    pWindow->onClose();
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    auto pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    pWindow->onMouseMovement(xPos, yPos);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    auto pWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    pWindow->onMouseScroll(xOffset, yOffset);
}

// Class functions
OpenGLContext::~OpenGLContext() {
    glfwTerminate();
}

bool OpenGLContext::init(Window* window) {
    // Call parent class init
    if(!RenderContext::init(window)) {
        std::cerr << "ERROR::OPENGL_CONTEXT::FAILED_TO_INIT_RENDER_CONTEXT" << std::endl;
    }

    // Initialize glfw and set version
    if(!glfwInit()) {
        std::cerr << "ERROR::OPENGL_CONTEXT::FAILED_TO_GLFW_INIT" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Initialize GLFWWindow
    window->window = glfwCreateWindow(window->width, window->height, window->programName.c_str(), nullptr, nullptr);
    if (!window->window) {
        std::cerr << "ERROR::OPENGL_CONTEXT::FAILED_TO_CREATE_WINDOW" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetWindowUserPointer(window->window, window);
    glfwSetFramebufferSizeCallback(window->window, framebuffer_size_callback);
    glfwSetWindowCloseCallback(window->window, on_window_close_callback);
    glfwSetCursorPosCallback(window->window, mouse_callback);
    glfwSetScrollCallback(window->window, scroll_callback);
    glfwMakeContextCurrent(window->window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "ERROR::OPENGL_CONTEXT::FAILED_TO_INIT_GLEW" << std::endl;
        return false;
    }

    return true;
}

void OpenGLContext::preRender() {
    glViewport(0, 0, pWindow->width, pWindow->height);
    // Set default background color
    glClearColor(0.94f, 0.93f, 0.81f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::postRender() {
    // Check and call events and swap the buffers
    glfwSwapBuffers(pWindow->window);
    glfwPollEvents();
}
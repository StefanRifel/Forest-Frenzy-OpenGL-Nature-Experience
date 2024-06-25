#include "../../include/context/OpenGLContext.hpp"

/**
 * @brief Class encapsulates the setup and management of an OpenGL rendering context using GLFW and GLEW. It initializes GLFW and GLEW, creates a window, sets up event callbacks, and manages basic OpenGL rendering operations such as clearing the screen and swapping buffers.
 */

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

bool OpenGLContext::init(Window* pWindow) {
    // Call parent class init
    if(!RenderContext::init(pWindow)) {
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
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Initialize GLFWWindow
    pWindow->window = glfwCreateWindow(pWindow->width, pWindow->height, pWindow->programName.c_str(), nullptr, nullptr);
    if (!pWindow->window) {
        std::cerr << "ERROR::OPENGL_CONTEXT::FAILED_TO_CREATE_WINDOW" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(pWindow->window);
    glfwSetWindowUserPointer(pWindow->window, pWindow);
    glfwSetFramebufferSizeCallback(pWindow->window, framebuffer_size_callback);
    glfwSetWindowCloseCallback(pWindow->window, on_window_close_callback);
    glfwSetCursorPosCallback(pWindow->window, mouse_callback);
    glfwSetScrollCallback(pWindow->window, scroll_callback);

    // Disable the cursor and lock it to the center of the specified window.
    // Useful for first-person camera controls.
    glfwSetInputMode(pWindow->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    glClearColor(0.38f, 0.42f, 0.48f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::postRender() {
    // Check and call events and swap the buffers
    glfwSwapBuffers(pWindow->window);
    glfwPollEvents();
}
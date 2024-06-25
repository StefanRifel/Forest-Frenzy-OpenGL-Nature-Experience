#include <utility>

#include "../include/Window.hpp"

/**
 * @brief Encapsulates the setup and management of a graphical window in a 3D graphics application
 */

Window::Window(int width, int height, std::string programName)
    : width {width}, height {height}, programName {std::move(programName)},
        window {nullptr}, openglContext{nullptr}, scene {nullptr}, isRunning {true} {

    openglContext = new OpenGLContext {};
    scene = new Scene {};
}

Window::~Window() {
    std::cout << "Good Bye!" << std::endl;
    glfwSetWindowShouldClose(window, true);
    delete(scene);
    delete(openglContext);
}

bool Window::init() {
    if(!openglContext->init(this)) {
        std::cerr << "ERROR::WINDOW::FAILED_TO_INIT_OPENGL_CONTEXT" << std::endl;
        return false;
    }
    if(!scene->init(this)) {
        std::cerr << "ERROR::WINDOW::FAILED_TO_INIT_SCENE" << std::endl;
        return false;
    }
    return true;
}

void Window::render() const {
    while (isRunning) {
        scene->processKeyboardInput();

        openglContext->preRender();
        
        scene->render();

        openglContext->postRender();
    }
}

void Window::onResize(int newWidth, int wenHeight) {
    this->width = newWidth;
    this->height = wenHeight;
}

void Window::onClose() {
    isRunning = false;
}

void Window::onMouseMovement(double xPos, double yPos) const {
    scene->processMouseInput(xPos, yPos);
}

void Window::onMouseScroll(double xOffset, double yOffset) const {
    scene->processMouseScrollInput(xOffset, yOffset);
}
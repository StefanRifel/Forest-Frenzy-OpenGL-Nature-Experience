#include <utility>

#include "../include/Window.hpp"

Window::Window(int width, int height, std::string programName)
    : width {width}, height {height}, programName {std::move(programName)}, window {nullptr}, isRunning {true} {

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
        scene->processInput();
        
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
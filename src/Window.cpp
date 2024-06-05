#include "../include/Window.hpp"

Window::Window(GLuint width, GLuint height, std::string programmName) 
: width {width}, height {height}, programmName {programmName}, 
window {nullptr}, isRunning {true} {
    openglContext = new OpenGLContext {};
    scene = new Scene {};
}

Window::~Window() {
    std::cout << "Good Bye!" << std::endl;
    glfwSetWindowShouldClose(window, true);
    delete(scene);
    delete(openglContext);
}

void Window::init() {
    if(!openglContext->init(this)) {
        std::cerr << "ERROR::WINDOW::FAILED_TO_INIT_OPENGLCONTEXT" << std::endl;
    }
    if(!scene->init(this)) {
        std::cerr << "ERROR::WINDOW::FAILED_TO_INIT_SCENE" << std::endl;
    }
}

void Window::render() {
    // render loop
    while (isRunning) {
        scene->processInput();
        
        openglContext->preRender();
        
        scene->render();

        openglContext->postRender();
    }
}

void Window::onResize(GLuint width, GLuint height) {
    this->width = width;
    this->height = height;
}

void Window::onClose() {
    isRunning = false;
}
#include "../include/Window.hpp"

Window::Window(GLuint width, GLuint height, std::string programmName) 
: width {width}, height {height}, programmName {programmName}, 
window {nullptr}, isRunning {true} {
    openglContext = new OpenGLContext {};
    guiContext = new GUIContext {};
    scene = new Scene {};
    uiPanel = new UIPanel {};
}

Window::~Window() {
    std::cout << "Good Bye!" << std::endl;
    glfwSetWindowShouldClose(window, true);
    delete(scene);
    delete(openglContext);
    delete(guiContext);
    delete(uiPanel);
}

void Window::init() {
    if(!openglContext->init(this)) {
        std::cerr << "ERROR::WINDOW::FAILED_TO_INIT_OPENGLCONTEXT" << std::endl;
    }
    if(!guiContext->init(this)) {
        std::cerr << "ERROR::WINDOW::FAILED_TO_INIT_GUICONTEXT" << std::endl;
    }
    if(!scene->init(this)) {
        std::cerr << "ERROR::WINDOW::FAILED_TO_INIT_SCENE" << std::endl;
    }
}

void Window::render() {
    // render loop
    while (isRunning) {
        // (Your code calls glfwPollEvents())
        scene->processInput();
        // ...
        // Start the Dear ImGui frame
        guiContext->preRender();
        uiPanel->render(scene);
        
        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        openglContext->preRender();
        
        scene->render();
        
        guiContext->postRender();
        // (Your code calls glfwSwapBuffers() etc.)

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
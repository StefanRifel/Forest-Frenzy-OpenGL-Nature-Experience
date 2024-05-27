#include "../include/WindowManager.hpp"

WindowManager::WindowManager(GLuint width, GLuint height, std::string programmName) 
: width {width}, height {height}, programmName {programmName}, 
window {nullptr}, isRunning {true} {
    openglContext = new OpenGLContext {};
    guiContext = new GUIContext {};
    uiPanel = new UIPanel {};
}

WindowManager::~WindowManager() {
    std::cout << "Good Bye!" << std::endl;
    glfwSetWindowShouldClose(window, true);
    delete(openglContext);
    delete(guiContext);
    delete(uiPanel);
}

void WindowManager::init() {
    // test implementaion ecs
    coordinator.init();
    coordinator.registerComponent<ecs::Renderable>();
    coordinator.registerComponent<ecs::Transform>();
    coordinator.registerComponent<ecs::Camera>();

    renderSystem = coordinator.registerSystem<RenderSystem>();
    {
        ecs::Signature signature;
        signature.set(coordinator.getComponentType<ecs::Renderable>());
        signature.set(coordinator.getComponentType<ecs::Transform>());
        coordinator.setSystemSignature<RenderSystem>(signature);
    }
    

    cameraControlSystem = coordinator.registerSystem<CameraControlSystem>();
    {
        ecs::Signature signature;
        signature.set(coordinator.getComponentType<ecs::Transform>());
        signature.set(coordinator.getComponentType<ecs::Camera>());
        coordinator.setSystemSignature<CameraControlSystem>(signature);
    }

    if(!openglContext->init(this)) {
        std::cerr << "ERROR::WINDOWMANAGER::FAILED_TO_INIT_OPENGLCONTEXT" << std::endl;
    }
    if(!guiContext->init(this)) {
        std::cerr << "ERROR::WINDOWMANAGER::FAILED_TO_INIT_GUICONTEXT" << std::endl;
    }
    if(!renderSystem->init(this, shader)) {
        std::cerr << "ERROR::WINDOWMANAGER::FAILED_TO_INIT_RENDERSYSTEM" << std::endl;
    }
    if(!cameraControlSystem->init(this)) {
        std::cerr << "ERROR::WINDOWMANAGER::FAILED_TO_INIT_CAMERACONTROLSYSTEM" << std::endl;
    }

    // create example object
    const char* path = "../assets/models/teapot.obj";
    vec3 color {0.04f, 0.88f, 0.69f};
    vec3 position {0.0f, 0.0f, 0.0f};
    renderSystem->createObject(path, color, position);

    //path = "../assets/models/earth.obj";
    //vec3 lightColor {1.0f, 1.0f, 1.0f};
    //shader.setColor(lightColor, "lightColor");
    //vec3 lightPos{2.0f, 1.5f, 5.0f};
    //renderSystem->createObject(path, lightColor, lightPos);
}

void WindowManager::render() {
    // render loop
    while (isRunning) {
        // (Your code calls glfwPollEvents())
        renderSystem->processInput();
        // ...
        // Start the Dear ImGui frame
        guiContext->preRender();
        uiPanel->render(coordinator);
        
        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        openglContext->preRender();
        
        cameraControlSystem->render(shader);
        renderSystem->render(shader);
        
        guiContext->postRender();
        // (Your code calls glfwSwapBuffers() etc.)

        openglContext->postRender();
    }
}

void WindowManager::onResize(GLuint width, GLuint height) {
    this->width = width;
    this->height = height;
}

void WindowManager::onClose() {
    isRunning = false;
}
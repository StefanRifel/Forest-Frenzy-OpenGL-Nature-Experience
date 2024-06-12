#include "../include/Scene.hpp"
#include "../include/renderable/Sun.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../libs/LoadImg/stb_image.h"

Scene::Scene() : window {nullptr} {}

Scene::~Scene() {
    for (Mesh* obj : renderable) {
        delete(obj);
    }
}

bool Scene::init(Window* pWindow) {
    this->window = pWindow;

    // create example object cube
    const char* CubePath = "../assets/models/teapot.obj";
    vector<Vertex> cubeVertices;
    OBJModelLoader::load(CubePath, cubeVertices);

    Tree* teapot  = new Tree {cubeVertices};

    vec3 cubeColor {255, 112, 112};
    teapot->setColor(cubeColor);

    addRenderableObject(teapot);

    // create example object sphere
    const char* sunPath = "../assets/models/sphere.obj";
    vector<Vertex> sunVertices;

    OBJModelLoader::load(sunPath, sunVertices);
    Sun* sun = new Sun {sunVertices};

    vec3 sunColor {253, 251, 211};
    sun->setColor(sunColor);

    addRenderableObject(sun);

    // scene settings
    cullFace(true);
    polygonModeRasterized(false);
    depthTest(true);

    return true;
}

void Scene::addRenderableObject(Mesh* object) {
    renderable.push_back(object);
}

void Scene::render() {
    for (Mesh* obj : renderable) {
        camera.look(obj->getShader());
        obj->draw();
    }
}

void Scene::cullFace(bool b) {
    b ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

void Scene::polygonModeRasterized(bool b) {
    b ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Scene::depthTest(bool b) {
    b ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void Scene::processKeyboardInput() {
    float currentFrame = static_cast<float>(glfwGetTime());
    camera.deltaTime = currentFrame - camera.lastFrame;
    camera.lastFrame = currentFrame;
    if(glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window->onClose();
    }
    if(glfwGetKey(window->window, GLFW_KEY_W)) {
        std::cout << "Camera Movement: FORWARD" << std::endl;
        camera.processKeyboard(FORWARD, camera.deltaTime);
    }
    if(glfwGetKey(window->window, GLFW_KEY_A)) {
        std::cout << "Camera Movement: LEFT" << std::endl;
        camera.processKeyboard(LEFT, camera.deltaTime);
    }
    if(glfwGetKey(window->window, GLFW_KEY_S)) {
        std::cout << "Camera Movement: BACKWARD" << std::endl;
        camera.processKeyboard(BACKWARD, camera.deltaTime);
    }
    if(glfwGetKey(window->window, GLFW_KEY_D)) {
        std::cout << "Camera Movement: RIGHT" << std::endl;
        camera.processKeyboard(RIGHT, camera.deltaTime);
    }
    if(glfwGetKey(window->window, GLFW_KEY_UP)) {
        std::cout << "Camera Movement: UP" << std::endl;
        camera.processKeyboard(UP, camera.deltaTime);
    }
    if(glfwGetKey(window->window, GLFW_KEY_DOWN)) {
        std::cout << "Camera Movement: DOWN" << std::endl;
        camera.processKeyboard(DOWN, camera.deltaTime);
    }
}

void Scene::processMouseInput(double xPos, double yPos) {
    camera.processMouseMovement(xPos, yPos, true);
}

void Scene::processMouseScrollInput(double xOffset, double yOffset) {
    camera.zoomWithMouseScroll(yOffset);
}
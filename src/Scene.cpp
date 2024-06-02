#include "../include/Scene.hpp"

Scene::Scene() : window {nullptr} {}

Scene::~Scene() {
    for (RenderableObject* obj : renderableObjects) {
        delete(obj);
    }
}

bool Scene::init(Window* window) {
    this->window = window;
    if(!shader.createShader("../shaders/shader.vs", "../shaders/shader.fs")) {
        std::cerr << "ERROR::SCENE::FAILED_TO_CREATE_SHADER" << std::endl;
        return false;
    }

    // create example object
    ModelLoader loader {};
    const char* path = "../assets/models/sphere.obj";
    std::vector<Vertex> inVertices;
    std::vector<GLuint> inFaces;
    loader.load(path, inVertices, inFaces);

    Mesh* teapot  = new Mesh {inVertices, inFaces};
    vec3 color {255, 112, 112};
    teapot->setColor(color);
    addRenderableObject(teapot);

    // scene settings
    cullFace(true);
    polygonModeRasterized(false);
    depthTest(true);

    return true;
}

void Scene::addRenderableObject(RenderableObject* object) {
    renderableObjects.push_back(object);
}

void Scene::render() {
    camera.look(shader);
    for (RenderableObject* obj : renderableObjects) {
        mat4 model {1.0f};
        shader.setModel(model);
        obj->draw(shader);
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

void Scene::onChangeColor(float color[4]) {
    for (auto obj : renderableObjects) {
        obj->setColor(vec3 {color[0], color[1], color[2]});
    }
    
}

void Scene::processInput() {
    if(glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window->onClose();
    }
    
/*
    const float cameraSpeed = 0.05f; // adjust accordingly

    // Zoom camera out = "." and in = ","
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
        camera->cameraPos.z() -= cameraSpeed;
        camera->radiusXZ = camera->cameraPos.z();
        std::cout << "zoom in: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
        camera->cameraPos.z() += cameraSpeed;
        camera->radiusXZ = camera->cameraPos.z();
        std::cout << "zoom out: " << camera->cameraPos << std::endl;
    }

    // change position and point of view of the camera
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera->cameraPos.y() += cameraSpeed;
        camera->cameraFront.y() += cameraSpeed;
        std::cout << "move camera up: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera->cameraPos.y() -= cameraSpeed;
        camera->cameraFront.y() -= cameraSpeed;
        std::cout << "move camera down: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera->cameraPos.x() -= cameraSpeed;
        camera->cameraFront.x() -= cameraSpeed;
        std::cout << "move camera left: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera->cameraPos.x() += cameraSpeed;
        camera->cameraFront.x() += cameraSpeed;
        std::cout << "move camera right: " << camera->cameraPos << std::endl;
    }

    // rotate model around in x and y axis
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->anlgeXZ--;
        vec3 newPos = Transformation::calcPointOnCircle(camera->anlgeXZ, camera->radiusXZ);
        camera->cameraPos.x() = newPos.x();
        camera->cameraPos.z() = newPos.y();
        std::cout << "turn camera around left: " << camera->cameraPos << std::endl;
    }
    

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->anlgeXZ++;
        vec3 newPos = Transformation::calcPointOnCircle(camera->anlgeXZ, camera->radiusXZ);
        camera->cameraPos.x() = newPos.x();
        camera->cameraPos.z() = newPos.y();
        std::cout << "turn camera around right: " << camera->cameraPos << std::endl;
    }
    */
}
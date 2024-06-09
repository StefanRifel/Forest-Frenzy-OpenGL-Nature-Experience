#include "../include/Scene.hpp"

Scene::Scene() : window {nullptr} {}

Scene::~Scene() {
    for (Mesh* obj : renderable) {
        delete(obj);
    }
}

bool Scene::init(Window* pWindow) {
    this->window = pWindow;

    // create example object
    const char* path = "../assets/models/sphere.obj";
    vector<Vertex> inVertices;
    vector<GLuint> inFaces;
    OBJModelLoader::load(path, inVertices, inFaces);

    Tree* teapot  = new Tree {inVertices, inFaces};
    vec3 color {255, 112, 112};
    teapot->setColor(color);

    addRenderableObject(teapot);

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

void Scene::processInput() const {
    if(glfwGetKey(window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        window->onClose();
    }
    
/*
    const float cameraSpeed = 0.05f; // adjust accordingly

    // Zoom camera out = "." and in = ","
    if (glfwGetKey(pWindow, GLFW_KEY_COMMA) == GLFW_PRESS) {
        camera->cameraPos.z() -= cameraSpeed;
        camera->radiusXZ = camera->cameraPos.z();
        std::cout << "zoom in: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(pWindow, GLFW_KEY_PERIOD) == GLFW_PRESS) {
        camera->cameraPos.z() += cameraSpeed;
        camera->radiusXZ = camera->cameraPos.z();
        std::cout << "zoom out: " << camera->cameraPos << std::endl;
    }

    // change position and point of view of the camera
    if (glfwGetKey(pWindow, GLFW_KEY_UP) == GLFW_PRESS) {
        camera->cameraPos.y() += cameraSpeed;
        camera->cameraFront.y() += cameraSpeed;
        std::cout << "move camera up: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(pWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera->cameraPos.y() -= cameraSpeed;
        camera->cameraFront.y() -= cameraSpeed;
        std::cout << "move camera down: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(pWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera->cameraPos.x() -= cameraSpeed;
        camera->cameraFront.x() -= cameraSpeed;
        std::cout << "move camera left: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(pWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera->cameraPos.x() += cameraSpeed;
        camera->cameraFront.x() += cameraSpeed;
        std::cout << "move camera right: " << camera->cameraPos << std::endl;
    }

    // rotate model around in x and y axis
    if (glfwGetKey(pWindow, GLFW_KEY_A) == GLFW_PRESS) {
        camera->anlgeXZ--;
        vec3 newPos = Transformation::calcPointOnCircle(camera->anlgeXZ, camera->radiusXZ);
        camera->cameraPos.x() = newPos.x();
        camera->cameraPos.z() = newPos.y();
        std::cout << "turn camera around left: " << camera->cameraPos << std::endl;
    }
    

    if (glfwGetKey(pWindow, GLFW_KEY_D) == GLFW_PRESS) {
        camera->anlgeXZ++;
        vec3 newPos = Transformation::calcPointOnCircle(camera->anlgeXZ, camera->radiusXZ);
        camera->cameraPos.x() = newPos.x();
        camera->cameraPos.z() = newPos.y();
        std::cout << "turn camera around right: " << camera->cameraPos << std::endl;
    }
    */
}
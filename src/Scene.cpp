#include "../include/Scene.hpp"

Scene::Scene() : window {nullptr} {}

Scene::~Scene() {
    for (Mesh* obj : renderable) {
        delete(obj);
    }
}

bool Scene::init(Window* pWindow) {
    this->window = pWindow;

    framebuffer = new Framebuffer {};

    terrain = new Terrain {"mud_forest_diff_1k.jpg"};

    auto* model = new Model {"street_rat_1k"};
    addRenderableModelObject(model);

    moon = new Moon {"moon"};
    //auto* model1 = new Model {"street_rat_1k"};
    //addRenderableModelObject(model1);

    //auto* model2 = new Model {"jacaranda_tree_1k"};
    //addRenderableModelObject(model2);

    skybox = new Skybox {"skybox"};

    // scene settings
    cullFace(true);
    polygonModeRasterized(false);
    depthTest(true);
    glEnable(GL_MULTISAMPLE);

    return true;
}

void Scene::addRenderableObject(Mesh* object) {
    renderable.push_back(object);
}

void Scene::render() {
    camera.look();

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
    glEnable(GL_DEPTH_TEST);

    glCullFace(GL_FRONT);
    terrain->draw(camera);
    glCullFace(GL_BACK);
    for (Model* model: renderableModel) {
        model->draw(camera);
    }
    moon->draw(camera);
    //skybox->draw(camera);

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    framebuffer->shader.use();
    glBindVertexArray(framebuffer->quadVAO);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, framebuffer->tcb);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

/*
 * Toggles face culling in the scene.
 * Face culling improves performance by not drawing faces of polygons that are
 * facing away from the camera. If b is true, enable face culling; if false, disable it.
 */
void Scene::cullFace(bool b) {
    b ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

/*
 * Sets the polygon rasterization mode in the scene.
 * When b is true, polygons are rendered in wireframe mode (outlines only).
 * When b is false, polygons are rendered in fill mode (solid).
 */
void Scene::polygonModeRasterized(bool b) {
    b ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/*
 * Toggles depth testing in the scene.
 * Depth testing ensures that pixels closer to the camera obscure pixels further away,
 * which is essential for rendering scenes correctly. If b is true, enable depth testing;
 * if false, disable it.
 */
void Scene::depthTest(bool b) {
    b ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void Scene::processKeyboardInput() {
    auto currentFrame = static_cast<float>(glfwGetTime());
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
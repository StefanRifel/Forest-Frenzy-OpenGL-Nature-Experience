#include "../include/Scene.hpp"

Scene::Scene() : window {nullptr} {}

bool Scene::init(Window* pWindow) {
    this->window = pWindow;

    framebuffer = new Framebuffer {};

    terrain = new Terrain {"leafy_grass_diff_1k.jpg"};
    moon = new Moon {"moon"};
    skybox = new Skybox {"skybox"};

    // Car
    Model* car = new Model {"covered_car_1k", "model"};
    mat4 carMat{1.0f};
    vec3 carTranslate {-7.0, 0.2, 2.0};
    carMat = Transformation::translate(carMat, carTranslate);
    car->setModelTranslation(carMat);
    addRenderableModelObject(car);

    // Rat
    Model* rat = new Model {"street_rat_1k", "model"};
    mat4 ratMat{1.0f};
    vec3 ratTranslate {-7.0, 1.6, 2.0};
    ratMat = Transformation::translate(ratMat, ratTranslate);
    rat->setModelTranslation(ratMat);
    addRenderableModelObject(rat);

    // Table
    Model* table = new Model {"wooden_picnic_table_1k", "model"};
    mat4 tableMat{1.0f};
    vec3 tableTranslate {4.0, 0.3, 0.0};
    tableMat = Transformation::translate(tableMat, tableTranslate);
    table->setModelTranslation(tableMat);
    addRenderableModelObject(table);

    // Chess Board
    Model* chessBoard = new Model {"chess_set_1k", "model"};
    mat4 chessBoardMat{1.0f};
    vec3 chessBoardTranslate {4.0, 1.04, 0.0};
    chessBoardMat = Transformation::translate(chessBoardMat, chessBoardTranslate);
    chessBoardMat = Transformation::rotateY(chessBoardMat, 17);
    chessBoard->setModelTranslation(chessBoardMat);
    addRenderableModelObject(chessBoard);

    // Dead Tree
    Model* deadTree = new Model {"dead_tree_trunk_02_1k", "model"};
    mat4 deadTreeMat{1.0f};
    vec3 deadTreeTranslate {4.0, 0.3, 10.0};
    deadTreeMat = Transformation::translate(deadTreeMat, deadTreeTranslate);
    deadTree->setModelTranslation(deadTreeMat);
    addRenderableModelObject(deadTree);

    // Fern
    auto* fern = new Model {"fern_02_1k", "instance_model", 350};
    addRenderableModelObject(fern);

    // Nettle
    auto* nettle = new Model {"nettle_plant_1k", "instance_model", 350};
    addRenderableModelObject(nettle);

    auto* tree_stump = new Model {"tree_stump_01_1k", "instance_model", 45};
    addRenderableModelObject(tree_stump);

    // scene settings
    cullFace(true);
    polygonModeRasterized(false);
    depthTest(true);
    glEnable(GL_MULTISAMPLE);

    return true;
}

void Scene::render() {
    camera.look();

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
    glEnable(GL_DEPTH_TEST);

    // Draw Scene
    glCullFace(GL_FRONT);
    terrain->draw(camera);
    glCullFace(GL_BACK);
    for (Model* model: renderableModel) {
        model->draw(camera);
    }
    moon->draw(camera);
    cullFace(false);
    skybox->draw(camera);
    //end

    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    framebuffer->postProcess();

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
        camera.processKeyboard(FORWARD, camera.deltaTime);
    }
    if(glfwGetKey(window->window, GLFW_KEY_A)) {
        camera.processKeyboard(LEFT, camera.deltaTime);
    }
    if(glfwGetKey(window->window, GLFW_KEY_S)) {
        camera.processKeyboard(BACKWARD, camera.deltaTime);
    }
    if(glfwGetKey(window->window, GLFW_KEY_D)) {
        camera.processKeyboard(RIGHT, camera.deltaTime);
    }
    bool uKeyIsPressed = (glfwGetKey(window->window, GLFW_KEY_U) == GLFW_PRESS);
    if (uKeyIsPressed && !uKeyWasPressed) {
        camera.setFlashlight(!camera.isFlashlight());
    }
    uKeyWasPressed = uKeyIsPressed;
}

void Scene::processMouseInput(double xPos, double yPos) {
    camera.processMouseMovement(xPos, yPos, true);
}

void Scene::processMouseScrollInput(double xOffset, double yOffset) {
    camera.zoomWithMouseScroll(yOffset);
}
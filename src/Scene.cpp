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
    moon = new Moon {"moon"};
    skybox = new Skybox {"skybox"};


    Model* model = new Model {"wooden_picnic_table_1k"};
    addRenderableModelObject(model);
    vec3 v1 {4.0, 0.3, 0.0};
    for (auto& a : model->meshes) {
        a.changePosition(v1);
    }

    auto* model1 = new Model {"street_rat_1k"};
    addRenderableModelObject(model1);
    vec3 v2 {4.0, 0.3, 4.0};
    vec3 s2 {35.0, 35.0, 35.0};
    for (auto& a : model1->meshes) {
        a.changePosition(v2);
        a.scale(s2);
    }


    auto* model2 = new Model {"brass_goblets_1k"};
    addRenderableModelObject(model2);
    vec3 v3 {4.0, 1.05, 0.0};
    for (auto& a : model2->meshes) {
        a.changePosition(v3);
    }

    std::random_device rd;  // Random device to seed the generator
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-50.0, 50.0); // Distribution for x and z positions

    for (int i = 0; i < 5; ++i) {
        auto* model5 = new Model {"fern_02_1k"};
        addRenderableModelObject(model5);

        // Generate random positions within the range -100 to 100 for x and z
        float x = static_cast<float>(dis(gen));
        float z = static_cast<float>(dis(gen));
        vec3 v5 {x, 0.3f, z};
        vec3 s5 {6.0f, 6.0f, 6.0f};

        // Apply position and scale transformations to all meshes in the model
        for (auto& a : model5->meshes) {
            a.changePosition(v5);
            a.scale(s5);
        }
    }

    std::uniform_real_distribution<> diss(-150.0, 150.0); // Distribution for x and z positions
    for (int i = 0; i < 5; ++i) {
        auto* model3 = new Model {"boulder_01_1k"};
        addRenderableModelObject(model3);

        // Generate random positions within the range -100 to 100 for x and z
        float x = static_cast<float>(diss(gen));
        float z = static_cast<float>(diss(gen));
        vec3 v5 {x, 0.3f, z};
        vec3 s5 {6.0f, 6.0f, 6.0f};

        // Apply position and scale transformations to all meshes in the model
        for (auto& a : model3->meshes) {
            a.changePosition(v5);
            a.scale(s5);
        }
    }

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
    moon->updateRotation(camera.deltaTime);

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
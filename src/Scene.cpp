#include "../include/Scene.hpp"

Scene::Scene() : window {nullptr} {}

Scene::~Scene() {
    for (Mesh* obj : renderable) {
        delete(obj);
    }
}

bool Scene::init(Window* pWindow) {
    this->window = pWindow;

    // obj paths
    const char* sunPath = "../assets/models/sphere.obj";
    const char* cubePath = "../assets/models/cube.obj";
    const char* skyboxPath = "../assets/models/skybox.obj";

    // texture paths
    const char* appleImg = "../assets/models/apple/Apple_Sphere.png";
    const char* face = "../assets/textures/awesomeface.png";
    const char* terrainTexture = "../assets/textures/terrain/coast_sand_rocks_02_diff_4k.jpg";

    vector<const char*> skyboxFaces;
    skyboxFaces.push_back("right.png");
    skyboxFaces.push_back("left.png");
    skyboxFaces.push_back("top.png");
    skyboxFaces.push_back("bottom.png");
    skyboxFaces.push_back("front.png");
    skyboxFaces.push_back("back.png");


    // terrain
    vector<Vertex> terrainVertices;
    vector<GLuint> terrainIndices;
    TextureLoader::simpleLoadTerrain(terrainVertices, terrainIndices);
    Terrain* terrain = new Terrain {terrainVertices, terrainIndices};
    TextureLoader::loadTexture(terrainTexture, terrain->getTextureID());


    // create example object sphere
    vector<Vertex> sunVertices;
    OBJModelLoader::load(sunPath, sunVertices);
    Sun* sun = new Sun {sunVertices};
    vec3 sunColor {253, 251, 211};
    sun->setColor(sunColor);
    //sun->setMaterial(MATERIAL_GOLD);

    // create example cube
    vector<Vertex> cubeVertices;
    OBJModelLoader::load(cubePath, cubeVertices);
    Tree* teapot  = new Tree {cubeVertices};
    //TextureLoader::loadTexture(face, teapot->getTextureID());
    TextureLoader::loadCubemap(skyboxFaces, teapot->getTextureID());
    vec3 cubeColor {0, 168, 107};
    teapot->setColor(cubeColor);
    teapot->setMaterial(MATERIAL_JADE);


    // skybox
    vector<Vertex> skyboxVertices;
    OBJModelLoader::load(skyboxPath, skyboxVertices);
    Skybox* skybox = new Skybox {skyboxVertices};
    TextureLoader::loadCubemap(skyboxFaces, skybox->getTextureID());

    addRenderableObject(terrain);
    addRenderableObject(sun);
    addRenderableObject(teapot);
    addRenderableObject(skybox);

    // scene settings
    cullFace(false);
    polygonModeRasterized(false);
    depthTest(true);

    return true;
}

void Scene::addRenderableObject(Mesh* object) {
    renderable.push_back(object);
}

void Scene::render() {
    for (Mesh* obj : renderable) {
        camera.look();
        obj->draw(camera);
    }
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
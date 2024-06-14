#include "../include/Scene.hpp"

Scene::Scene() : window {nullptr} {}

Scene::~Scene() {
    for (Mesh* obj : renderable) {
        delete(obj);
    }
}

bool Scene::init(Window* pWindow) {
    this->window = pWindow;
/*
    // skybox
    vector<const char*> skyboxFaces;
    skyboxFaces.push_back("right.jpg");
    skyboxFaces.push_back("left.jpg");
    skyboxFaces.push_back("top.jpg");
    skyboxFaces.push_back("bottom.jpg");
    skyboxFaces.push_back("front.jpg");
    skyboxFaces.push_back("back.jpg");

    const char* skyboxPath = "../assets/models/skybox.obj";
    vector<Vertex> skyboxVertices;
    OBJModelLoader::load(skyboxPath, skyboxVertices);
    Skybox* skybox = new Skybox {skyboxVertices};
    TextureLoader::loadCubemap(skyboxFaces, skybox->getTextureID());
    addRenderableObject(skybox);
*/
    // Terrain.cpp
    const char* terrainTexture = "../assets/textures/terrain/coast_sand_rocks_02_diff_4k.jpg";
    vector<Vertex> terrainVertices;
    vector<GLuint> terrainIndices;
    int numStrips;
    int numTrisPerStrip;
    //TextureLoader::loadTerrain("../assets/textures/height_map_africa.png", terrainVertices, terrainIndices, numStrips, numTrisPerStrip);
    TextureLoader::simpleLoadTerrain(terrainVertices, terrainIndices);
    //Terrain* terrain = new Terrain {terrainVertices, terrainIndices, numStrips, numTrisPerStrip};
    Terrain* terrain = new Terrain {terrainVertices, terrainIndices};
    TextureLoader::loadTexture(terrainTexture, terrain->getTextureID());
    addRenderableObject(terrain);

    // create example object sphere
    const char* sunPath = "../assets/models/sphere.obj";
    vector<Vertex> sunVertices;

    OBJModelLoader::load(sunPath, sunVertices);
    Sun* sun = new Sun {sunVertices};

    vec3 sunColor {253, 251, 211};
    sun->setColor(sunColor);
    sun->setMaterial(MATERIAL_GOLD);

    addRenderableObject(sun);

    const char* AppleImg = "../assets/models/apple/Apple_Sphere.png";
    const char* face = "../assets/textures/awesomeface.png";

    const char* CubePath = "../assets/models/cube.obj";
    vector<Vertex> cubeVertices;
    OBJModelLoader::load(CubePath, cubeVertices);

    Tree* teapot  = new Tree {cubeVertices};

    TextureLoader::loadTexture(terrainTexture, teapot->getTextureID());

    vec3 cubeColor {0, 168, 107};
    teapot->setColor(cubeColor);
    teapot->setMaterial(MATERIAL_JADE);

    addRenderableObject(teapot);


    // scene settings
    cullFace(false);
    polygonModeRasterized(false);
    depthTest(false);

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
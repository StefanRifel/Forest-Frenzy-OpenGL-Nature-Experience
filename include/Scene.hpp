#ifndef SCENE_HH
#define SCENE_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Window.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "loader/OBJModelLoader.hpp"
#include "loader/TextureLoader.hpp"
#include "loader/AssetLoader.hpp"
#include "renderable/Model.h"

class Scene {
public:
    Window* window;

    vector<Mesh*> renderable;
    vector<Model*> renderableModel;
    Camera camera;

public:
    Scene();
    ~Scene();

    bool init(Window* pWindow);

    void addRenderableObject(Mesh* object);
    void addRenderableModelObject(Model* object) {
        renderableModel.push_back(object);
    }

    // different pWindow settings
    static void cullFace(bool b);
    static void polygonModeRasterized(bool b);
    static void depthTest(bool b);

    void render();
    void processKeyboardInput();
    void processMouseInput(double xPos, double yPos);
    void processMouseScrollInput(double xOffset, double yOffset);
};

#endif
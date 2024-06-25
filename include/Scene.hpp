#ifndef SCENE_HH
#define SCENE_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "renderable/Framebuffer.h"
#include "Window.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "loader/OBJModelLoader.hpp"
#include "loader/TextureLoader.hpp"
#include "loader/AssetLoader.hpp"
#include "renderable/Model.h"
#include "renderable/Skybox.hpp"
#include "renderable/Terrain.hpp"
#include "renderable/Moon.hpp"

/**
 * @brief Class provides a structured approach to managing and rendering a scene in an OpenGL application. It encapsulates the rendering objects (Model, Skybox, Terrain, Moon), camera settings (Camera), input handling, and OpenGL state management
 */

class Scene {
public:
    Window* window;

    vector<Model*> renderableModel;
    Skybox* skybox {nullptr};
    Terrain* terrain {nullptr};
    Moon* moon {nullptr};
    Camera camera;
    Framebuffer* framebuffer {nullptr};

public:
    bool uKeyWasPressed = false;

    Scene();
    ~Scene() = default;

    bool init(Window* pWindow);

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
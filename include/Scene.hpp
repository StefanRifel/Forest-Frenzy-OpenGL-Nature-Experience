#ifndef SCENE_HH
#define SCENE_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Window.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "RenderableObject.hpp"
#include "OBJModelLoader.hpp"
#include "Mesh.hpp"

class Scene {
public:
    Window* window;

    vector<RenderableObject*> renderableObjects;
    Camera camera;
    Shader shader;

public:
    Scene();
    ~Scene();

    bool init(Window* window);

    void addRenderableObject(RenderableObject* object);

    // different window settings
    void cullFace(bool b);
    void polygonModeRasterized(bool b);
    void depthTest(bool b);

    void onChangeColor(float color[4]);

    void render();
    void processInput();
};

#endif
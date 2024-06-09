#ifndef SCENE_HH
#define SCENE_HH

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Window.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "OBJModelLoader.hpp"
#include "Tree.hpp"

class Scene {
public:
    Window* window;

    vector<Mesh*> renderable;
    Camera camera;

public:
    Scene();
    ~Scene();

    bool init(Window* pWindow);

    void addRenderableObject(Mesh* object);

    // different pWindow settings
    static void cullFace(bool b);
    static void polygonModeRasterized(bool b);
    static void depthTest(bool b);

    void render();
    void processInput() const;
};

#endif
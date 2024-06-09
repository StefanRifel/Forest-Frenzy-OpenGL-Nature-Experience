#ifndef WINDOW_HH
#define WINDOW_HH

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLContext;
#include "context/OpenGLContext.hpp"
class Scene;
#include "Scene.hpp"

/**
 * @brief The Window class represents a pWindow for rendering OpenGL content.
 *
 * This class is responsible for creating and managing a GLFW pWindow, initializing the OpenGL context,
 * and rendering the scene.
 */
class Window {
public:
    GLFWwindow* window; ///< Pointer to the GLFW pWindow object.
    
    std::string programName; ///< The name of the program.
    int width; ///< The width of the pWindow.
    int height; ///< The height of the pWindow.

    bool isRunning; ///< Flag indicating whether the pWindow is running.
    
    OpenGLContext* openglContext; ///< Pointer to the OpenGL context.
    Scene* scene; ///< Pointer to the scene to be rendered.

public:
    /**
     * @brief Constructs a Window object with the specified width, height, and program name.
     *
     * @param width The width of the pWindow.
     * @param height The height of the pWindow.
     * @param programName The name of the program.
     */
    Window(int width, int height, std::string programName);
    /**
     * @brief Destructor for the Window class.
     */
    ~Window();
    /**
     * @brief Initializes the pWindow and the OpenGL context.
     *
     * @return True if initialization was successful, false otherwise.
     */
    bool init();
    /**
     * @brief Renders the scene in the pWindow.
     */
    void render() const;

    /**
     * @brief Handles pWindow resize events.
     *
     * @param width The new width of the pWindow.
     * @param height The new height of the pWindow.
     */
    void onResize(int width, int height);
    /**
     * @brief Handles pWindow close events.
     */
    void onClose();
};

#endif
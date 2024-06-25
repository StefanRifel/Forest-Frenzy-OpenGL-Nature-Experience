#include "../include/Window.hpp"

/**
 * @brief Initializes and runs an OpenGL window application titled "Forest Frenzy - OpenGL Nature Experience", handling initialization errors and rendering through a dynamically allocated Window object, ensuring proper memory management by deleting the object at the end
 */

int main() {
    std::cout << "Welcome to \"Forest Frenzy - OpenGL Nature Experience!\"" << std::endl;

    auto* window = new Window {1024, 768, "Forest Frenzy"};

    if (!window->init()) {
        std::cerr << "Failed to initialize the pWindow." << std::endl;
        return -1;
    }

    window->render();
    delete(window);
    return 0;
}
#include "../include/Window.hpp"

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
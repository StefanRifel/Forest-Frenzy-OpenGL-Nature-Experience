#include "../include/Window.hpp"

int main(void) {
    std::cout << "Welcome to OpenGL Odyssey!" << std::endl;

    Window* window = new Window {1024, 768, "OpenGL-Odyssey"};
    window->init();
    window->render();
    delete(window);

    return 0;
}
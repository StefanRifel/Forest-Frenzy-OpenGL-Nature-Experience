#include "../include/WindowManager.hpp"

int main(void) {
    std::cout << "Welcome to OpenGL Odyssey!" << std::endl;
    
    WindowManager* windowManager = new WindowManager {1024, 768, "OpenGL-Odyssey"};
    windowManager->init();
    windowManager->render();
    delete(windowManager);

    return 0;
}
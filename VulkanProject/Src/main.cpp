#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "App.h"
#include <iostream>

int main() {
    App app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
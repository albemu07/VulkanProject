#include "App.h"

#include <iostream>

void App::run()
{
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void App::initWindow()
{
    glfwInit();

    //GLFW initializes with opengl by default. This is for disabling it. The second disables resizable window.
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void App::createInstance()
{
    //Check ValidationLayers only in debug mode
    if (enableValidationLayers) checkValidationLayerSupport();

    //Optional. Application Info.
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "First Try";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    //Not optional. Tells driver which extensions and validation layers we want to use.
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    //Get the extensions form GLFW
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    //Create Vulkan Instance and store it in instance. 
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    //CREATE FUNCTION TO CHECK ALL GLFW EXTENSIONS ARE IN THE SUPPORTED LIST
    checkGLFWExtensions(extensions, createInfo);
}

void App::checkGLFWExtensions(const std::vector<VkExtensionProperties>& extensions, const VkInstanceCreateInfo& createInfo)
{
    //takes de glfw extension array names and compares them to the extensions in the vulkan supported list
    for (int i = 0; i < createInfo.enabledExtensionCount; i++) {
        bool found = false;
        for (const auto& extension : extensions) {
            if (strcmp(extension.extensionName, createInfo.ppEnabledExtensionNames[i]) == 0) {
                found = true;
                break;
            }
        }

        if (!found) throw std::runtime_error("missin vulkan extension");
    }
        std::cout << "extension requirements fulfilled" << std::endl;
}

void App::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool found = false;
        for (const auto& layer : availableLayers) {
            if (strcmp(layer.layerName, layerName) == 0) {
                found = true;
                break;
            }
        }

        if (!found) throw std::runtime_error("validation layer requested, but not available");

        std::cout << "layer requirements fulfilled" << std::endl;
    }
}

void App::initVulkan()
{
    createInstance();
}

void App::mainLoop()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void App::cleanup()
{
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
}

#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#define WIDTH 800
#define HEIGHT 600

//Validation Layers
const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

//Run validation layers only in debug
#ifdef NDEBUG
const bool enableDebugSteps = false;
#else
const bool enableDebugSteps = true;
#endif


class App {

public:
	void run();
private:
	void initWindow();
	void createInstance();
	std::vector<const char*> getRequiredExtension();
	void checkGLFWExtensions(const std::vector<VkExtensionProperties>& extensions, const VkInstanceCreateInfo& createInfo);
	void checkValidationLayerSupport();
	void initVulkan();
	void mainLoop();
	void cleanup();

	GLFWwindow* window;
	VkInstance instance;
};
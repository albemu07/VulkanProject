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

//Extension function not loaded have to look up address using vkGetInstanceProcAddr
// our proxy function QUE SIGNIFICA ESTO LUEGO LO BUSCAS ESPABILA
//VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
//	const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
//	auto func = 
//}

class App {

public:
	void run();
private:
	void initWindow();
	void createInstance();
	void setupDebugMessenger();
	std::vector<const char*> getRequiredExtension();
	void checkGLFWExtensions(const std::vector<VkExtensionProperties>& extensions, const VkInstanceCreateInfo& createInfo);
	void checkValidationLayerSupport();
	void initVulkan();
	void mainLoop();
	void cleanup();
	//Callbacks
	// 
	//static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(); This is the same but supported for other platforms
	static VkBool32 __stdcall debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	GLFWwindow* window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
};
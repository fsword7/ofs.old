/*
 * main.cpp - main SDL2 program
 *
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#include <iostream>

#include <SDL2/SDL.h>
//#include <vulkan/vulkan.h>
//#include <GL/GL.h>
//#include <GL/glew.h>

#include "main/main.h"
#include "main/coreapp.h"

#define APP_FULL_NAME	"Orbital Flight Simulator"
#define APP_SHORT_NAME	"OFS"

using namespace ofs;

//VkInstance instance;
//
//const VkApplicationInfo appInfo = {
//		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
//		.pNext = nullptr,
//		.pApplicationName = APP_SHORT_NAME,
//		.applicationVersion = 0,
//		.pEngineName = APP_SHORT_NAME,
//		.engineVersion = 0,
//		.apiVersion = VK_API_VERSION_1_0,
//};
//
//const VkInstanceCreateInfo createInfo = {
//		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
//		.pNext = nullptr,
//		.flags = 0,
//		.pApplicationInfo = &appInfo,
//		.enabledLayerCount = 0,
//		.ppEnabledLayerNames = nullptr,
//		.enabledExtensionCount = 0,
//		.ppEnabledExtensionNames = nullptr,
//};

//void initVulkan()
//{
//	VkResult   result;
//
//	// create instance
//	result = vkCreateInstance(&createInfo, nullptr, &instance);
//	if (result != VK_SUCCESS) {
//		std::cerr << "Failed to create Vulkan instance: " << result << std::endl;
//		abort();
//	}
//
//
//	// create physical devices
//
//}
//
//void cleanVulkan()
//{
//
//
//	vkDestroyInstance(instance, nullptr);
//}

// Initialize SDL2 facility with Vulkan/OpenGL
void CoreApplication::init()
{
	SDL_Window       *dWindow;
	SDL_Renderer     *dRenderer;
	SDL_RendererInfo  dRendererInfo;

//	VkInstance   instance;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "OFS: Unable to initialize SDL: " << SDL_GetError() << std::endl;
		abort();
	}
	atexit(SDL_Quit);

	// OpenGL window/full screen
//	SDL_CreateWindowAndRenderer(1600, 1200, SDL_WINDOW_OPENGL,
//			&dWindow, &dRenderer);
//	SDL_GetRendererInfo(dRenderer, &dRendererInfo);

//	dWindow = SDL_CreateWindow("Orbital Flight Simulator",
//			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//			1280, 720, SDL_WINDOW_SHOWN|SDL_WINDOW_VULKAN);


}

void CoreApplication::clean()
{
//	cleanVulkan();
}

int main(int argc, char **argv)
{
	CoreApplication &app = *new CoreApplication();

	std::cout << "Orbital Flight Simulator" << std::endl;

	app.init();



	SDL_Delay(5000);
	app.clean();

	return 0;
}

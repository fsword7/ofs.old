/*
 * main.cpp - main SDL2 program
 *
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#include <iostream>

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>
//#include <GL/GL.h>
//#include <GL/glew.h>

#include "main/main.h"
#include "main/core.h"

using namespace ofs;

// Initialize SDL2 facility with Vulkan/OpenGL
void Core::onInit()
{
	SDL_Window       *dWindow;
	SDL_Renderer     *dRenderer;
	SDL_RendererInfo  dRendererInfo;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "OFS: Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return;
	}
	atexit(SDL_Quit);

	// OpenGL window/full screen
//	SDL_CreateWindowAndRenderer(1600, 1200, SDL_WINDOW_OPENGL,
//			&dWindow, &dRenderer);
//	SDL_GetRendererInfo(dRenderer, &dRendererInfo);



}

void Core::onClean()
{
}

int main(int argc, char **argv)
{
	Core &app = *new Core();

	std::cout << "Orbital Flight Simulator" << std::endl;

	app.onInit();



	SDL_Delay(5000);
	app.onClean();

	return 0;
}

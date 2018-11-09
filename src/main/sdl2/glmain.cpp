/*
 * glmain.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: Tim Stark
 */

#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "main/main.h"
#include "main/coreapp.h"

using namespace ofs;

// Initialize SDL2 facility with OpenGL
void CoreApp::init()
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

	dWindow = SDL_CreateWindow(APP_FULL_NAME,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			OFS_DEFAULT_WIDTH, OFS_DEFAULT_HEIGHT,
			SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cerr << "GLEW Error: " << glewGetErrorString(err) << endl;
		exit(1);
	} else
		cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << endl;

}

void CoreApp::clean()
{
//	cleanVulkan();
}

int main(int argc, char **argv)
{
	CoreApp &app = *new CoreApp();

	std::cout << "Orbital Flight Simulator" << std::endl;

	app.init();



	SDL_Delay(5000);
	app.clean();

	return 0;
}




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
#include "main/sdl2/coreapp.h"

using namespace ofs;

// Initialize SDL2 facility with OpenGL
void sdlCoreApp::init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "OFS: Unable to initialize SDL: " << SDL_GetError() << std::endl;
		abort();
	}
	atexit(SDL_Quit);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// OpenGL window/full screen
	dWindow = SDL_CreateWindow(APP_FULL_NAME,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			OFS_DEFAULT_WIDTH, OFS_DEFAULT_HEIGHT,
			SDL_WINDOW_OPENGL /* |SDL_WINDOW_RESIZABLE */);
	if (dWindow == nullptr) {
		cerr << "SDL2 Window can't be created: " << SDL_GetError() << endl;
		exit(1);
	}
	auto ctx = SDL_GL_CreateContext(dWindow);


	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cerr << "GLEW Error: " << glewGetErrorString(err) << endl;
		exit(1);
	} else {
		cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << endl;
		cout << "  OpenGL version:   " << glGetString(GL_VERSION) << endl;
	}
}

void sdlCoreApp::clean()
{
}

void sdlCoreApp::run()
{
	bool running = true;

	while (running) {
		SDL_Event event;

		while(SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				running = false;
		}

		tick();
		paint();
		SDL_GL_SwapWindow(dWindow);
	}
}

int main(int argc, char **argv)
{
	CoreApp &app = *new sdlCoreApp();


	std::cout << "Orbital Flight Simulator" << std::endl;

	app.init();
	app.initEngine();
	app.initRenderer();

	app.run();

	app.clean();

	return 0;
}




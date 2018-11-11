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

SDL_Window *dWindow;

// Initialize SDL2 facility with OpenGL
void CoreApp::init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "OFS: Unable to initialize SDL: " << SDL_GetError() << std::endl;
		abort();
	}
	atexit(SDL_Quit);

	// OpenGL window/full screen
	dWindow = SDL_CreateWindow(APP_FULL_NAME,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			OFS_DEFAULT_WIDTH, OFS_DEFAULT_HEIGHT,
			SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
	if (dWindow == nullptr) {
		cerr << "SDL2 Window can't be created: " << SDL_GetError() << endl;
		exit(1);
	}
	auto ctx = SDL_GL_CreateContext(dWindow);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		cerr << "GLEW Error: " << glewGetErrorString(err) << endl;
		exit(1);
	} else {
		cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << endl;
		cout << "  OpenGL version:   " << glGetString(GL_VERSION) << endl;
	}
}

void CoreApp::clean()
{
}

int main(int argc, char **argv)
{
	CoreApp &app = *new CoreApp();
	bool run = true;

	std::cout << "Orbital Flight Simulator" << std::endl;

	app.init();
	app.initEngine();
	app.initRenderer();

	while (run) {
		SDL_Event event;

		while(SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				run = false;
		}

		app.tick();
		app.paint();
		SDL_GL_SwapWindow(dWindow);
	}

	app.clean();

	return 0;
}




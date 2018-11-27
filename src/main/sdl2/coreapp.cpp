/*
 * coreapp.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: Tim Stark
 */

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "main/main.h"
#include "main/sdl2/coreapp.h"

using namespace ofs;

sdlCoreApp::sdlCoreApp()
: CoreApp(),
  dWindow(nullptr)
{
}

sdlCoreApp::~sdlCoreApp()
{
}

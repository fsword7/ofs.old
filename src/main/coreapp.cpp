/*
 * core.cpp - OFS Core application
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/coreapp.h"
#include "engine/render/render.h"

using namespace ofs;

CoreApp::CoreApp()
: render(nullptr)
{
}

CoreApp::~CoreApp()
{
}

void CoreApp::initRenderer()
{
	// Initialize OpenGL-based Renderer
	render = new glRenderer();

	render->init(0, 0);
}

void CoreApp::initEngine()
{
}

void CoreApp::tick()
{
}

void CoreApp::paint()
{
	if (render != nullptr)
		render->paint();
}

void CoreApp::resize(int w, int h)
{
	if (render != nullptr)
		render->resize(w, h);
}

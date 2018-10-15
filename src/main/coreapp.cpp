/*
 * core.cpp - OFS Core application
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "main/coreapp.h"
#include "engine/engine.h"
#include "engine/player.h"
#include "engine/universe/universe.h"
#include "engine/render/scene.h"

using namespace ofs;

CoreApp::CoreApp()
: player(nullptr),
  engine(nullptr),
  universe(nullptr),
  scene(nullptr),
  width(OFS_DEFAULT_WIDTH),
  height(OFS_DEFAULT_HEIGHT)
{
}

CoreApp::~CoreApp()
{
	if (scene != nullptr)
		delete scene;
	if (universe != nullptr)
		delete universe;
	if (engine != nullptr)
		delete engine;
	if (player != nullptr)
		delete player;

}

void CoreApp::initRenderer()
{
	// Initialize OpenGL-based Renderer
	scene = new glScene();

	scene->init(width, height);
}

void CoreApp::initEngine()
{

	player = new Player();
	universe = new Universe();
	engine = new Engine(universe);
}

void CoreApp::tick()
{
}

void CoreApp::paint()
{
	if (scene != nullptr && player != nullptr && universe != nullptr)
		scene->paint(*player, *universe);
}

void CoreApp::resize(int w, int h)
{
	width = w;
	height = h;
	if (scene != nullptr)
		scene->resize(w, h);
}

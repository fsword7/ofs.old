/*
 * core.cpp - OFS Core application
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/engine.h"
#include "engine/player.h"
#include "universe/universe.h"
#include "render/scene.h"
#include "main/coreapp.h"

using namespace ofs;
//using namespace ofsu;

CoreApp::CoreApp()
: player(nullptr),
  engine(nullptr),
  universe(nullptr),
  scene(nullptr),
  width(OFS_DEFAULT_WIDTH),
  height(OFS_DEFAULT_HEIGHT)
{
	// Initialize state keys
	for (int key = 0; key < 256; key++)
		stateKey[key] = false;

	// Initialize velocity control
	keyRotationAccel = toRadian(OFS_DEFAULT_FOV);
	keyTravelAccel   = 2.0;
	keyTravelBrake   = 10.0;

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

	universe->init();
}

void CoreApp::pressKey(keyCode code, bool down)
{
	stateKey[code] = down;
}

void CoreApp::tick()
{
	double  dt = 1.0;
	vec3d_t rv;
	double  tv;

//	rv = player->getRotationVelocity();
//	tv = player->getTravelSpeed();

	// Keyboard rotation and travel control
	// X-axis rotation control
	if (stateKey[keyPad8] || stateKey[keyUp])
		rv += vec3d_t(dt * -keyRotationAccel, 0, 0);
	if (stateKey[keyPad2] || stateKey[keyDown])
		rv += vec3d_t(dt * keyRotationAccel, 0, 0);

	// Y-axis rotation control
	if (stateKey[keyPad4] || stateKey[keyLeft])
		rv += vec3d_t(0, dt * -keyRotationAccel, 0);
	if (stateKey[keyPad6] || stateKey[keyRight])
		rv += vec3d_t(0, dt * keyRotationAccel, 0);

	// Z-axis rotation control
	if (stateKey[keyPad7])
		rv += vec3d_t(0, 0, dt * keyRotationAccel);
	if (stateKey[keyPad9])
		rv += vec3d_t(0, 0, dt * -keyRotationAccel);

	// Travel velocity control
	if (stateKey[keyPad1])
		tv -= dt * 1000.0;
	if (stateKey[keyPad3])
		tv += dt * 1000.0;

	// Braking velocity control
	if (stateKey[keyPad5])
	{
		rv *= exp(-dt * keyRotationAccel);
		tv *= exp(-dt * keyTravelAccel);
	}

//	player->setRotationVelocity(rv);
//	player->setTravelSpeed(tv);

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

/*
 * scene.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/player.h"
#include "engine/universe/universe.h"
#include "engine/universe/body.h"
#include "engine/render/scene.h"
#include "engine/render/vobject.h"

Scene::Scene()
: width(1), height(1)
{
}

Scene::~Scene()
{
}

glScene::glScene()
: Scene(), vobj(nullptr)
{
}

glScene::~glScene()
{
}

void glScene::init(int w, int h)
{

	glLoadIdentity();

	resize(w, h);
}

void glScene::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width  = w;
	height = h;
}

void glScene::paint(Player &player, Universe &universe)
{
	Camera *cam;
	vec3d_t cpos;
	quatd_t crot;
	float   cfov;

	// get main camera from player for position and orientation.
	cam  = player.getCamera(0);
	cpos = cam->position();
	crot = cam->rotation();
	cfov = cam->getFOV();

//	glClearColor(1.0, 0.0, 0.0, 0.0);

	if (vobj == nullptr)
		vobj = new vPlanet(universe.earth, this);

	vobj->update(player);
	vobj->paint();
}

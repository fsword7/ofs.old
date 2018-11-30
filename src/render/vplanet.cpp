/*
 * vplanet.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/object.h"
#include "render/vobject.h"
#include "render/terrainmgr.h"
#include "render/gl/funcs.h"

vPlanet::vPlanet(Object *obj, Scene *scene)
: vObject(obj, scene)
{
	terrain = new TerrainManager(this);
}

vPlanet::~vPlanet()
{
	if (terrain != nullptr)
		delete terrain;
}

void vPlanet::paint()
{
	glTranslate(cpos);

	if (terrain != nullptr)
		terrain->paint();
}

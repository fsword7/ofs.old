/*
 * vplanet.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/object.h"
#include "engine/render/vobject.h"
#include "engine/render/terrainmgr.h"
#include "engine/render/gl/funcs.h"

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
	glTranslate(opos);

	if (terrain != nullptr)
		terrain->paint();
}

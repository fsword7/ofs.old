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

vPlanet::vPlanet(const Object *obj, const Scene *scene)
: vObject(obj, scene)
{
	terrain = new TerrainManager(this);
}

vPlanet::~vPlanet()
{
}

void vPlanet::paint()
{

}

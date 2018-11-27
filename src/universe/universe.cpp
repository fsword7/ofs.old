/*
 * universe.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/object.h"
#include "universe/stardb.h"
#include "universe/body.h"
#include "universe/star.h"
#include "universe/universe.h"

Universe::Universe()
{
	sol = nullptr;
	earth = nullptr;

	stardb = new StarDatabase();
}

Universe::~Universe()
{
	if (stardb != nullptr)
		delete stardb;
}

void Universe::init()
{



	// Temporary hacks for testing - to be removed later
	string solName = "Sol";
	sol = new CelestialStar(solName);

	string earthName = "Earth";
//	vec3d_t earthPos = vec3d_t(0, 0, -20000.0);
	vec3d_t earthPos = vec3d_t(0, 0, -3.0);

	earth = new CelestialBody(earthName);
	earth->setRadius(6371.0);
	earth->setPosition(earthPos);
}

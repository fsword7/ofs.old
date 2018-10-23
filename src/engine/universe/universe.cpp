/*
 * universe.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/object.h"
#include "engine/universe/body.h"
#include "engine/universe/universe.h"

Universe::Universe()
{
	earth = nullptr;
}

Universe::~Universe()
{
}

void Universe::init()
{



	// Temporary hacks for testing - to be removed later
//	sol = new CelestialStar("Sol");
	string earthName = "Earth";
	earth = new CelestialBody(earthName);
	earth->setRadius(6378.1);
}


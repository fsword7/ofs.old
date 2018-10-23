/*
 * body.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/universe/body.h"

CelestialBody::CelestialBody(string& name)
: Object(name, ObjectType::objCelestialBody)
{

}

CelestialBody::~CelestialBody()
{
}


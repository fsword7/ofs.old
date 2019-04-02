/*
 * body.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/body.h"

CelestialBody::CelestialBody(string& name)
: Object(name, ObjectType::objCelestialBody)
{

}

CelestialBody::~CelestialBody()
{
}

string CelestialBody::getFolder() const
{
	string pname;

	pname = "../data/systems/Sol/" + name() + "/";

	return pname;
}

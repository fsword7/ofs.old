/*
 * body.h - celestial body
 *
 *  Created on: Oct 22, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "engine/object.h"

class CelestialBody : public Object
{
public:
	CelestialBody(string& name);
	~CelestialBody();

private:
};

/*
 * star.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/star.h"

CelestialStar::CelestialStar(string& name)
: Object(name, ObjectType::objCelestialStar)
{

}

CelestialStar::~CelestialStar()
{
}


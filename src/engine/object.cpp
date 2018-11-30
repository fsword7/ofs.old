/*
 * object.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/object.h"

Object::Object(string name, ObjectType type)
: objType(type), objNames(1),
  objRadius(0), objSemiAxes(0, 0, 0),
  objMass(0), objAlbedo(1.0),
  objPosition(0, 0, 0)
{
	objNames[0] = name;
}

Object::~Object()
{
	objNames.clear();
}

string Object::name(int idx)
{
	if (idx >= objNames.size())
		return "";
	return objNames[idx];
}

string Object::name(int idx) const
{
	if (idx >= objNames.size())
		return "";
	return objNames[idx];
}

vec3d_t Object::position(double)
{
	return objPosition;
}


void Object::setRadius(double rad)
{
	objRadius   = rad;
	objSemiAxes = vec3d_t(rad, rad, rad);
}

void Object::setPosition(vec3d_t pos)
{
	objPosition = pos;
}

string Object::getFolder() const
{
	return "";
}

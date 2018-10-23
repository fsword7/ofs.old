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
: objType(type), objNames(1)
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

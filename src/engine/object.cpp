/*
 * object.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/object.h"

Object::Object(std::string name)
: names(1)
{
	names[0] = name;
}

Object::~Object()
{
	names.clear();
}




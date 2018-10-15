/*
 * vobject.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/object.h"
#include "engine/render/vobject.h"

vObject::vObject(const Object *_obj, const Scene *_scene)
: obj(_obj), scene(_scene)
{
}

vObject::~vObject()
{
}




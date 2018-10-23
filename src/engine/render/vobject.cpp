/*
 * vobject.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/player.h"
#include "engine/object.h"
#include "engine/render/vobject.h"

vObject::vObject(Object *_obj, Scene *_scene)
: obj(_obj), scene(_scene),
  visible(false), point(false),
  radius(0), cpos(0, 0, 0), cdist(0)
{
}

vObject::~vObject()
{
}

void vObject::update(Player& player)
{
	Camera *cam = player.getCamera(0);

	opos  = obj->position(0);
	cpos  = opos - cam->position();
	cdist = cpos.length();
}


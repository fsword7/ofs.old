/*
 * vobject.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/player.h"
#include "engine/object.h"
#include "render/vobject.h"

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
	cdist = glm::distance(opos, cpos);

//	cout << fixed << setprecision(10);
//	cout << "Camera:   (" << cpos.x << "," << cpos.y << "," << cpos.z << ")" << endl;
//	cout << "Object:   (" << opos.x << "," << opos.y << "," << opos.z << ")" << endl;
//	cout << "Distance: " << cdist << endl;

}


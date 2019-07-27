/*
 * scene.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/player.h"
#include "render/scene.h"

double Scene::calculatePixelSize(Camera *cam) const
{
	return 2 * tan(cam->getFOV()/2.0) / (double)height;
}



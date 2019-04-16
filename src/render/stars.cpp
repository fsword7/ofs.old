/*
 * stars.cpp - Star renderer
 *
 *  Created on: Apr 2, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/scene.h"
#include "render/stars.h"

StarVertexBuffer::StarVertexBuffer(const Scene &scene, int maxStars)
: scene(scene),
  type(useNotUsed),
  maxStars(maxStars),
  nStars(0),
  flagStarted(false)
{
	buffer.resize(maxStars);
}

StarVertexBuffer::~StarVertexBuffer()
{
	buffer.clear();
}

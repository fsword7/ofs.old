/*
 * stars.cpp - Stars rendering for OpenGL interface
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/scene.h"
#include "render/gl/stars.h"

void glScene::initStarVertexBuffer()
{

}

// ***********************************************************

glStarVertexBuffer::glStarVertexBuffer(const Scene &scene, int maxStars)
: StarVertexBuffer(scene, maxStars)
{
}

glStarVertexBuffer::~glStarVertexBuffer()
{
	finish();
}

void glStarVertexBuffer::startPoints()
{

}

void glStarVertexBuffer::startSprites()
{

}

void glStarVertexBuffer::render()
{

}

void glStarVertexBuffer::finish()
{

}

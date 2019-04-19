/*
 * stars.cpp - Stars rendering for OpenGL interface
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/scene.h"
#include "render/gl/shadermgr.h"
#include "render/gl/stars.h"

void glScene::initStarVertex()
{
	starRenderer = new glStarVertex(*this, 2048);
	starRenderer->startSprites();
}

// ***********************************************************

glStarVertex::glStarVertex(const Scene &scene, int maxStars)
: StarVertex(scene, maxStars)
{
}

glStarVertex::~glStarVertex()
{
	finish();
}

void glStarVertex::startPoints()
{

}

void glStarVertex::startSprites()
{
	ShaderProperties prop;

	prop.starShader = true;
	prop.type = ShaderProperties::shrPointStar;
	scene.getShaderManager()->createShader(prop);
}

void glStarVertex::render()
{

}

void glStarVertex::finish()
{

}

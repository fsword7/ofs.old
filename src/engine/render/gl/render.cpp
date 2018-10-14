/*
 * render.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/render/render.h"
#include "engine/player.h"
#include "engine/universe/universe.h"

Renderer::Renderer()
: width(1), height(1)
{
}

Renderer::~Renderer()
{
}

glRenderer::glRenderer()
: Renderer()
{
}

glRenderer::~glRenderer()
{
}

void glRenderer::init(int w, int h)
{

	glLoadIdentity();

	resize(w, h);
}

void glRenderer::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width  = w;
	height = h;
}

void glRenderer::paint(Player &player, Universe &universe)
{
	Camera *cam;
	vec3d_t cpos;
	quatd_t crot;
	float   cfov;

	// get main camera from player for position and orientation.
	cam  = player.getCamera(0);
	cpos = cam->getPosition();
	crot = cam->getRotation();
	cfov = cam->getFOV();

//	glClearColor(1.0, 0.0, 0.0, 0.0);
}

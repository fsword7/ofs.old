/*
 * stars.cpp - Stars rendering for OpenGL interface
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/stardb.h"
#include "render/gl/scene.h"
#include "render/gl/shader.h"
#include "render/gl/shadermgr.h"
#include "render/gl/stars.h"

void glScene::initStarVertex()
{
	StarVertex *starBuffer;

	starBuffer = new glStarVertex(*this, 2048);
//	starBuffer->startPoints();

	starRenderer = new StarRenderer();
	starRenderer->starBuffer = starBuffer;
}

void glScene::renderStars(const StarDatabase &stardb, const Player &player,
	double faintest)
{

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
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_TEXTURE_2D);

	uint32_t stride = sizeof(starVertex);
	glVertexPointer(3, GL_DOUBLE, stride, &buffer[0].posStar);
	glColorPointer(4, GL_UNSIGNED_SHORT, stride, &buffer[0].color);
	glPointSize(1.0);

	nStars = 0;
	type = usePoints;
	flagStarted = true;
}

void glStarVertex::startSprites()
{
	ShaderProperties prop;

	prop.starShader = true;
	prop.type = ShaderProperties::shrPointStar;

	glShaderPackage *pkg = dynamic_cast<glShaderPackage*>(scene.getShaderManager()->createShader(prop));
	if (pkg == nullptr)
		return;

	pkg->use();
	pkg->pointScale = 1.0;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableVertexAttribArray(glShaderPackage::PointSizeAttributeIndex);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	uint32_t stride = sizeof(starVertex);
	glVertexPointer(3, GL_DOUBLE, stride, &buffer[0].posStar);
	glColorPointer(4, GL_UNSIGNED_SHORT, stride, &buffer[0].color);
	glVertexAttribPointer(glShaderPackage::PointSizeAttributeIndex,
		1, GL_FLOAT, GL_FALSE, stride, &buffer[0].size);

	nStars = 0;
	type = useSprites;
	flagStarted = true;
}

void glStarVertex::render()
{
	if (nStars == 0)
		return;

	// Now rendering stars
	glDrawArrays(GL_POINTS, 0, nStars);
	nStars = 0;
}

void glStarVertex::finish()
{

	render();

	flagStarted = false;

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	switch (type) {
	case useSprites:
		glUseProgram(0);
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
		glDisable(GL_POINT_SPRITE);
		break;
	case usePoints:
	default:
		break;
	}
	type = useNotUsed;
}

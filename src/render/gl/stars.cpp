/*
 * stars.cpp - Stars rendering for OpenGL interface
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/player.h"
#include "universe/astro.h"
#include "universe/constellations.h"
#include "universe/star.h"
#include "universe/stardb.h"
#include "universe/universe.h"
#include "render/gl/scene.h"
#include "render/gl/shader.h"
#include "render/gl/shadermgr.h"
#include "render/gl/stars.h"

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
	if (txImage != nullptr)
		txImage->bind();
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

// ***********************************************************

void glScene::initStarVertex()
{
	StarVertex *starBuffer;
	StarColors *starColors;
	std::string fname = "../data/stars/bbr_color_D58.txt";

	starColors = new StarColors();
	starColors->load(fname);

	starBuffer = new glStarVertex(*this, 2048);

	starRenderer = new StarRenderer();
	starRenderer->scene = this;
	starRenderer->starBuffer = starBuffer;
	starRenderer->starColors = starColors;
}

void glScene::renderStars(const StarDatabase &stardb, const Player &player,
	double faintest)
{
	vec3d_t obs = player.getPosition() / KM_PER_PC;
	quatd_t rot = player.getRotation();
	Camera *cam = player.getCamera(0);
	double  fov = cam->getFOV();
//	double  aspect = cam->getAspect();

	starRenderer->cpos = cam->getPosition();
	starRenderer->pxSize = calculatePixelSize(cam);
	starRenderer->faintestMag = faintest;
//	starRenderer->starColors = starColors;
	starRenderer->starBuffer->startPoints();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
////	std::cout << "### Starting star renderer..." << std::endl;
////	stardb.findVisibleStars(starHandler, player, faintestMag);
	stardb.findVisibleStars(*starRenderer, obs, rot, fov, aspect, faintest);
	starRenderer->starBuffer->finish();
	glDisable(GL_BLEND);
}

void glScene::renderConstellations(const Universe &universe, const Player &player)
{
	const Constellations &constellations = universe.getConstellations();
	const StarDatabase &stardb = universe.getStarDatabase();

	Camera *cam = player.getCamera(0);
	vec3d_t cpos = cam->position();
	vec3d_t buffer[2];

	const std::vector<Asterism *> &asterisms = constellations.getAsterisms();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, &buffer[0]);
	glColor4f(0.7, 0.7, 0.7, 1.0);

	for (int idx = 0; idx < asterisms.size(); idx++) {
		Asterism *aster = asterisms[idx];
		for (int sidx = 0; sidx < aster->hip.size(); sidx += 2) {
			CelestialStar *star1 = stardb.getHIPStar(aster->hip[sidx]);
			CelestialStar *star2 = stardb.getHIPStar(aster->hip[sidx+1]);

			if (star1 == nullptr)
				std::cout << "HIP " << aster->hip[sidx] << " Missing" << std::endl;
			if (star2 == nullptr)
				std::cout << "HIP " << aster->hip[sidx+1] << " Missing" << std::endl;
			if (star1 == nullptr || star2 == nullptr)
				continue;

			buffer[0] = star1->getPosition(0) * KM_PER_PC;
			buffer[1] = star2->getPosition(0) * KM_PER_PC;
//			std::cout << "HIP: " << aster->hip[sidx]
//					  << " Name: " << star->name(0) << std::endl;
			glDrawArrays(GL_LINES, 0, 2);
		}
//		std::cout << std::endl;
	}

	glDisableClientState(GL_VERTEX_ARRAY);
}

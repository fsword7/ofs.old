/*
 * stars.h
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#pragma once

#include "render/stars.h"

class glStarVertex : public StarVertex
{
public:
	glStarVertex(const Scene &scene, int maxStars = 1000);
	~glStarVertex();

	// Render routines
	void startPoints() override;
	void startSprites() override;
	void render() override;
	void finish() override;

private:
	glShaderPackage *pkg;
};

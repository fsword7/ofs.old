/*
 * stars.h
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#pragma once

#include "render/stars.h"

class glStarVertexBuffer : public StarVertexBuffer
{
public:
	glStarVertexBuffer(const Scene &scene, int maxStars = 1000);
	~glStarVertexBuffer();

	// Render routines
	void startPoints() override;
	void startSprites() override;
	void render() override;
	void finish() override;
};

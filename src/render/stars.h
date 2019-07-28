/*
 * stars.h - star rendering
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#pragma once

#include "universe/stardb.h"
#include "render/starcolors.h"

class StarVertex
{
public:
	enum pointType {
		useNotUsed = 0,
		usePoints,
		useSprites
	};

	struct starVertex
	{
		vec3d_t		posStar;
		float		size;
		uint16_t	color[4];
	};

	StarVertex(const Scene &scene, int maxStars = 1000);
	virtual ~StarVertex();

	// Render routines
	virtual void startPoints() = 0;
	virtual void startSprites() = 0;
	virtual void render() = 0;
	virtual void finish() = 0;

	void addStar(const vec3d_t &pos, const Color &color, double size);

protected:
	const Scene &scene;
	pointType type;
	int  maxStars, nStars;
	bool flagStarted;

	std::vector<starVertex> buffer;
};

class StarRenderer : public ofsHandler
{
public:
	StarRenderer() = default;
	~StarRenderer()
	{
		if (starBuffer != nullptr)
			delete starBuffer;
	}

	void process(const CelestialStar& star, double dist, double appMag) const;

public:
	vec3d_t obsPos = { 0, 0, 0 }; // Observer's camera position

	// Star buffer for rendering
	StarVertex *starBuffer = nullptr;

	Scene  *scene = nullptr;     // Scene handler
	vec3d_t cpos;    // Current camera/player position
	double  pxSize;  // Pixel size
	double  faintestMag;
	double  size;

	StarColors *starColors = nullptr;

};

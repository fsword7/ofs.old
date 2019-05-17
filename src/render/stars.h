/*
 * stars.h - star rendering
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#pragma once

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

//	inline void addStar(const vec3d_t &pos, const Color &color, double size)
//	{
//		if (nStars < maxStars) {
//			nStars++;
//		} else {
//			render();
//			nStars = 0;
//		}
//	}

protected:
	const Scene &scene;
	pointType type;
	int  maxStars, nStars;
	bool flagStarted;

	std::vector<starVertex> buffer;
};

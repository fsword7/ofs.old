/*
 * scene.h - Scene rendering facility
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#pragma once

class Player;
class Universe;
class vObject;

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void init(int w, int h) = 0;
	virtual void resize(int w, int h) = 0;
	virtual void paint(Player &player, Universe &universe) = 0;

protected:
	int    width, height;
	double aspect;
};

class StarVertexBuffer
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
		double		size;
		uint16_t	color[4];
	};

	StarVertexBuffer(const Scene &scene, int maxStars = 1000);
	virtual ~StarVertexBuffer();

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

#define DIST_NEAR	0.001
#define DIST_FAR	1.0e9

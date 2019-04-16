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
class CelestialStar;

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

	std::vector<const CelestialStar *> closeStars;
};

#define DIST_NEAR	0.001
#define DIST_FAR	1.0e9

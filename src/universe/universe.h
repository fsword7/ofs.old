/*
 * universe.h - Universe engine class
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

class StarDatabase;
class CelestialBody;
class CelestialStar;
class Constellations;

#include "universe/constellations.h"

class Universe {
public:
	Universe();
	~Universe();

	void init();

	StarDatabase &getStarDatabase() const { return *stardb; }

	int findCloseStars(const vec3d_t& obs, double mdist,
			std::vector<const CelestialStar *>& stars) const;

	CelestialBody *earth;
	CelestialStar *sol;

private:
	StarDatabase *stardb;
	Constellations constellations;
};

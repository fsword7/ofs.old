/*
 * universe.h - Universe engine class
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

class CelestialBody;
class CelestialStar;

class Universe {
public:
	Universe();
	~Universe();

	void init();

	CelestialBody *earth;
	CelestialStar *sol;

private:
	vector<CelestialStar *> unsortedStars;
};

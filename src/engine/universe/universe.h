/*
 * universe.h - Universe engine class
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

class CelestialBody;

class Universe {
public:
	Universe();
	~Universe();

	void init();

private:
	CelestialBody *earth;
};

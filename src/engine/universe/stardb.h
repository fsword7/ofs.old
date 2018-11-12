/*
 * stardb.h
 *
 *  Created on: Nov 12, 2018
 *      Author: Tim Stark
 */

#pragma once

class CelestialStar;

class StarDatabase
{
public:
	StarDatabase();
	~StarDatabase();

private:
	vector<CelestialStar *> unsortedStars;
};

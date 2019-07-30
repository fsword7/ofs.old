/*
 * universe.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/object.h"
#include "universe/astro.h"
#include "universe/body.h"
#include "universe/constellations.h"
#include "universe/star.h"
#include "universe/stardb.h"
#include "universe/universe.h"

Universe::Universe()
{
	sol = nullptr;
	earth = nullptr;

	stardb = new StarDatabase();
}

Universe::~Universe()
{
	if (stardb != nullptr)
		delete stardb;
}

void Universe::init()
{
//	std::string fname = "../data/stars/hygdata_v3.csv";
//	stardb->loadHYGData(fname);

	std::string pname = "../data/stars/xhip";
	stardb->loadXHIPData(pname);

	std::string cname = "../data/constellations/western/constellationship.fab";
//	std::string cname = "../data/constellations/western_rey/constellationship.fab";
	constellations.load(cname);

	string earthName = "Earth";
//	vec3d_t earthPos = vec3d_t(0, 0, -20000.0);
	vec3d_t earthPos = vec3d_t(0, 0, -3.0);

	earth = new CelestialBody(earthName);
	earth->setRadius(6371.0);
	earth->setPosition(earthPos);
}

class CloseStarHandler : public ofsHandler
{
public:
	CloseStarHandler(double mdist, std::vector<const CelestialStar *> &stars)
		: maxDistance(mdist), nStars(stars) {};
	~CloseStarHandler() {};

	void process(const CelestialStar& star, double dist, double) const
	{
		if (dist < maxDistance)
			nStars.push_back(&star);
	}

private:
	double maxDistance;
	std::vector<const CelestialStar *> &nStars;

};

int Universe::findCloseStars(const vec3d_t& obs, double mdist,
		vector<const CelestialStar *>& stars) const
{
	CloseStarHandler handle(mdist, stars);
	vec3d_t lobs = obs / KM_PER_PC;
	int count;

	if (stardb == nullptr)
		return 0;
	stardb->findNearStars(handle, lobs, mdist);

//	cout << "Near stars: " << count << " stars" << std::endl;
//	if (count > 0)
//		cout << "Star name: " << stars[0]->getName() << std::endl;

	return stars.size();
}

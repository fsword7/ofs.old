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

//class Player;
//class StarHandler;
//class StarTree;
//class CelestialStar;
//
//class ofsHandler {
//public:
//	ofsHandler() {};
//	virtual ~ofsHandler() {};
//
//	virtual void process(const CelestialStar& star, double dist, double appMag) const = 0;
//};
//
//class StarDatabase
//{
//public:
//	StarDatabase();
//	~StarDatabase();
//
//	bool loadHYGData(const std::string& fname);
//	bool loadXHIPData(const std::string& pname);
//
//    void finish();
//
////    void findVisibleStars(const ofsHandler& handle, const Player& player, double faintestMag);
////    int  findNearStars(const vec3d_t& obs, double mdist,
////    		std::vector<const CelestialStar *>& stars) const;
//
//    void findVisibleStars(const ofsHandler& handle, const vec3d_t& obs,
//    	const quatd_t &rot, double fov, double aspect, double limitMag) const;
//    void findNearStars(const ofsHandler& handle, const vec3d_t& obs,
//    	double radius) const;
//
//    CelestialStar *find(const std::string& name) const;
//
//protected:
//    void initOctreeData(std::vector<CelestialStar*> stars);
//
//private:
//	std::vector<CelestialStar*> uStars;  // Unsorted stars for loading purposes
//
//	StarTree *starTree;
//};

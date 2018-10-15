/*
 * terrainmgr.h - Terrain manager facility
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

class vPlanet;

class Tile {
	Tile(int lod, int ilat, int ilng);
	~Tile();

private:
	int lod;
	int ilat, ilng;

};

class TerrainManager {
public:
	TerrainManager(vPlanet *vobj);
	~TerrainManager();

private:
	vPlanet *vobj;

//	Tile *tree[2]; // Western/Eastern hemisphere
};

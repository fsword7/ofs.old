/*
 * terrainmgr.h - Terrain manager facility
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

class Tile {
	Tile();
	~Tile();

private:
	int ilat, ilng;
	int nlat, nlng;
	int lod;
};

class TerrainManager {
public:
	TerrainManager();
	~TerrainManager();

private:

};

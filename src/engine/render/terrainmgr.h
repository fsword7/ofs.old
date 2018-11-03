/*
 * terrainmgr.h - Terrain manager facility
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "util/tree.h"

class vPlanet;

class Tile : public Tree<QTREE_NODES>
{
public:
	Tile();
	virtual ~Tile();

	virtual int load();

protected:

};

class TerrainTile : public Tile
{
public:
	TerrainTile(int lod, int ilat, int ilng);
	~TerrainTile();

	int load();

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

	TerrainTile *terrain[2]; // Western/Eastern hemisphere
};

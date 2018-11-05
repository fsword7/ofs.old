/*
 * terrainmgr.h - Terrain manager facility
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "util/tree.h"

class vPlanet;

class QuadTile : public Tree<QTREE_NODES>
{
public:
	QuadTile(int lod, int ilat, int ilng);
	virtual ~QuadTile();

	virtual int load();

protected:
	int lod;
	int ilat, ilng;
};

class TerrainTile : public QuadTile
{
public:
	TerrainTile(int lod, int ilat, int ilng);
	~TerrainTile();

	int load();

private:

};

class TerrainManager {
public:
	TerrainManager(vPlanet *vobj);
	~TerrainManager();

private:
	vPlanet *vobj;

	TerrainTile *terrain[2]; // Western/Eastern hemisphere
};

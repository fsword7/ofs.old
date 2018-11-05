/*
 * terrainmgr.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/render/terrainmgr.h"

QuadTile::QuadTile(int _lod, int _ilat, int _ilng)
: lod(_lod), ilat(_ilat), ilng(_ilng)
{
}

QuadTile::~QuadTile()
{
}

int QuadTile::load()
{
	return 0;
}


TerrainTile::TerrainTile(int lod, int ilat, int ilng)
: QuadTile(lod, ilat, ilng)
{

}

TerrainTile::~TerrainTile()
{
}

int TerrainTile::load()
{
	return 0;
}

TerrainManager::TerrainManager(vPlanet *_vobj)
: vobj(_vobj)
{

	// Initialize root of terrain tiles
	for (int idx = 0; idx < 2; idx++) {
		terrain[idx] = new TerrainTile(0, 0, idx);
		terrain[idx]->load();
	}
}

TerrainManager::~TerrainManager()
{

	// Delete all root tiles
	for (int idx = 0; idx < 2; idx++)
		delete terrain[idx];

}

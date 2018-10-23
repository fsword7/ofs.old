/*
 * terrainmgr.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/render/terrainmgr.h"

Tile::Tile(int _lod, int _ilat, int _ilng)
: lod(_lod), ilat(_ilat), ilng(_ilng)
{

}

Tile::~Tile()
{
}


TerrainManager::TerrainManager(vPlanet *_vobj)
: vobj(_vobj)
{

	// Initialize root tiles
//	for (int idx = 0; idx < 2; idx++)
//		tree[idx] = new Tile(0, 0, idx);
}

TerrainManager::~TerrainManager()
{

	// Delete all root tiles
//	for (int idx = 0; idx < 2; idx++)
//		delete tree[idx];

}

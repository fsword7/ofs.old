/*
 * terrainmgr.h - Terrain manager facility
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "util/tree.h"

class vPlanet;
class glMesh;
class TerrainManager;
class zTreeManager;
class ImageTexture;

// Texture Coordination Range
template <typename T>
struct tcRange
{
	T tumin, tumax;
	T tvmin, tvmax;
};

typedef tcRange<float>  tcrf_t;
typedef tcRange<double> tcrd_t;

class QuadTile : public Tree<QuadTile, QTREE_NODES>
{
public:
	QuadTile(TerrainManager *mgr, int lod, int ilat, int ilng);
	virtual ~QuadTile();

	virtual int load();

protected:
	TerrainManager *mgr;

	int lod;
	int ilat, ilng;
};

class TerrainTile : public QuadTile
{
public:
	TerrainTile(TerrainManager *mgr, int lod, int ilat, int ilng);
	~TerrainTile();

	int  load();
	void paint();

	enum tileState {
		Invalid = 0x0000,
		InQueue = 0x0001,
		Loading = 0x0002,
		NoImage = 0x0004
	};

private:
	glMesh *mesh;

	tileState state;
	tcrd_t txRange;

	ImageTexture *txImage = nullptr;
	bool txOwn = false;
};

class TerrainManager {
	friend class TerrainTile;

public:
	TerrainManager(vPlanet *vobj);
	~TerrainManager();

	void paint();

//	glMesh *createSpherePatch(int lod, int ilat, int ilng, int grids,
//		tcRange2 &tcr, const int16_t *elev, double elevGlobe, double elevScale);
	glMesh *createSpherePatch(int lod, int ilat, int ilng, int grids, tcrd_t &tcr);

private:
	Scene *scene;
	vPlanet *vobj;

	zTreeManager *ztree[5];

	TerrainTile *terrain[2]; // Western/Eastern hemisphere
};

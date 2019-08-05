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
class Texture;

#define TILE_RENDER		0x2000
#define TILE_ACTIVE		0x4000
#define TILE_VALID		0x8000

// Texture Coordination Range
template <typename T>
struct tcRange
{
	T tumin, tumax;
	T tvmin, tvmax;
};

typedef tcRange<float>  tcrf_t;
typedef tcRange<double> tcrd_t;

struct RenderParm
{
	int       maxLOD;
    int       lodBias;

	// Planet status parameters (in global frame)
	mat4d_t   pwmat;     // Planet world matrix
	mat4d_t   pwmat_tmp; // Planet world matrix temporary
	mat3d_t   prot;      // Planet rotation matrix
	vec3d_t   ppos;      // Planet position

	// Camera status parameters (in planet frame)
	mat3d_t   crot;  // Camera rotation matrix
	vec3d_t   cpos;  // Camera position
	vec3d_t   cdir;  // Camera direction from planet centre
	double    cdist; // Camera distance from planet

	double    viewap;
	double    tanap;
	mat4d_t   pvmat; // Projection/View matrix for frustum
};

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
	friend class TerrainManager;

public:
	TerrainTile(TerrainManager *mgr, int lod, int ilat, int ilng);
	~TerrainTile();

	inline Texture *getTexture() { return txImage; }

	void setSubTexCoordRange(const tcrd_t &ptcr);

	int  load();
	void render();

	enum tileState {
		Invalid		= 0x0000,
		InQueue		= 0x0001,
		Loading		= 0x0002,
		NoImage		= 0x0004,
		Inactive	= TILE_VALID,
		Invisible	= TILE_VALID,
		Rendering	= TILE_VALID|TILE_RENDER
	};

private:
	glMesh *mesh;

	tileState state;
	tcrd_t txRange;

	Texture *txImage = nullptr;
	bool txOwn = false;
};

class TerrainManager {
	friend class TerrainTile;

public:
	TerrainManager(vPlanet *vobj);
	~TerrainManager();

	// Rendering terrain area
	void process(TerrainTile *tile);
	void render(TerrainTile *tile);
	void render();

//	glMesh *createSpherePatch(int lod, int ilat, int ilng, int grids,
//		tcRange2 &tcr, const int16_t *elev, double elevGlobe, double elevScale);
	glMesh *createSpherePatch(int lod, int ilat, int ilng, int grids, tcrd_t &tcr);

private:
	void setRenderParm(RenderParm &prm);

private:
	Scene *scene;
	vPlanet *vobj;

	zTreeManager *ztree[5];

	TerrainTile *terrain[2]; // Western/Eastern hemisphere
};

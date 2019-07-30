/*
 * terrainmgr.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/object.h"
#include "render/vobject.h"
#include "render/image.h"
#include "render/texture.h"
#include "render/scene.h"
#include "render/terrainmgr.h"
#include "render/ztreemgr.h"
#include "render/gl/mesh.h"
#include "util/dds.h"

static tcrd_t fullRange = { 0.0, 1.0, 0.0, 1.0 };

QuadTile::QuadTile(TerrainManager *_mgr, int _lod, int _ilat, int _ilng)
: mgr(_mgr), lod(_lod), ilat(_ilat), ilng(_ilng)
{
}

QuadTile::~QuadTile()
{
}

int QuadTile::load()
{
	return 0;
}


TerrainTile::TerrainTile(TerrainManager *mgr, int lod, int ilat, int ilng)
: QuadTile(mgr, lod, ilat, ilng),
  mesh(nullptr), state(Invalid), txRange(fullRange)
{

}

TerrainTile::~TerrainTile()
{
	if (mesh != nullptr)
		delete mesh;
	if (txImage != nullptr && txOwn == true)
		delete txImage;
}

void TerrainTile::setSubTexCoordRange(const tcrd_t &ptcr)
{
	if ((ilng & 1) == 0) { // Right column
		txRange.tumin = (ptcr.tumin + ptcr.tumax) / 2.0;
		txRange.tumax = ptcr.tumax;
	} else {       // Left column
		txRange.tumin = ptcr.tumin;
		txRange.tumax = (ptcr.tumin + ptcr.tumax) / 2.0;
	}

	if (ilat & 1) { // Top row
		txRange.tvmin = (ptcr.tvmin + ptcr.tvmax) / 2.0;
		txRange.tvmax = ptcr.tvmax;
	} else {       // Bottom row
		txRange.tvmin = ptcr.tvmin;
		txRange.tvmax = (ptcr.tvmin + ptcr.tvmax) / 2.0;
	}
}

int TerrainTile::load()
{
	ddsLoader dds;
	uint8_t  *ddsImage = nullptr;
	Image    *image = nullptr;
	uint32_t  szImage = 0;
	int       res;

	state = Loading;

    if (image == nullptr && mgr->ztree[0] != nullptr) {
        res = szImage = mgr->ztree[0]->read(lod+4, ilat, ilng, &ddsImage);
        if (res > 0 && ddsImage != nullptr) {
            image = dds.load(ddsImage, szImage);
            delete []ddsImage;
//            std::cout << "Image loaded" << std::endl;
        }
    }

    if (image == nullptr) {
    	// Non-existent tile. Have to load
    	// lower LOD tile from parent tile
    	// and set sub texture range.
    	TerrainTile *ptile = dynamic_cast<TerrainTile *>(getParent());
    	if (ptile != nullptr) {
    		txImage = ptile->getTexture();
    		txOwn   = false;
    		setSubTexCoordRange(ptile->txRange);
//    		std::cout << "Subtexture created" << std::endl;
    	}
    } else {
        txImage = mgr->scene->createTexture(image);
        txOwn   = true;
//        std::cout << "Texture created" << std::endl;
    }

	mesh = mgr->createSpherePatch(lod, ilat, ilng, 32, txRange);
	if (mesh != nullptr)
		mesh->txImage = txImage;
//	state = Inactive;
	return 0;
}

void TerrainTile::render()
{
	if (mesh != nullptr)
		mesh->paint();
}

TerrainManager::TerrainManager(vPlanet *vobj)
: scene(vobj->getScene()), vobj(vobj)
{
	string pname;

	pname = vobj->object()->getFolder() + "/ztree";

	// Initailize ztree database for tile image loading
	for (int idx = 0; idx < 4; idx++)
		ztree[idx] = nullptr;
	ztree[0] = zTreeManager::create(pname, "surf");

	// Initialize root of terrain tiles
	for (int idx = 0; idx < 2; idx++) {
		terrain[idx] = new TerrainTile(this, 0, 0, idx);
		terrain[idx]->load();
	}
}

TerrainManager::~TerrainManager()
{

	// Delete all root tiles
	for (int idx = 0; idx < 2; idx++)
		delete terrain[idx];

}

void TerrainManager::process(TerrainTile *tile)
{

	int lod  = tile->lod;
	int nlat = 1 << tile->ilat;
	int nlng = 2 << tile->ilng;

	tile->state = TerrainTile::Rendering;

}

void TerrainManager::render(TerrainTile *tile)
{

	if (tile->state == TerrainTile::Rendering)
		tile->render();
//	else if (tile->state == TerrainTfile::Active)
//	{
//		for (int idx = 0; idx < 4; idx++) {
//			TerrainTile *child = tile->getChild(idx);
//			if (child != nullptr && (child->state & TILE_ACTIVE))
//				render(child);
//		}
//	}
}

void TerrainManager::render()
{

	// Rendering terrain area
	for (int idx = 0; idx < 2; idx++)
		process(terrain[idx]);
	for (int idx = 0; idx < 2; idx++)
		render(terrain[idx]);
}

// Create spherical patch/hemisphere for LOD level 0+
//glMesh *TerrainManager::createSpherePatch(int lod, int ilat, int ilng, int grids,
//	tcRange2 &tcr, const int16_t *elev, double elevGlobe, double elevScale)
glMesh *TerrainManager::createSpherePatch(int lod, int ilat, int ilng,
		int grids, tcrd_t &tcr)
{
	int nlat = 1 << lod;
	int nlng = 2 << lod;

	double mlat0 = PI * double(ilat) / double(nlat);
	double mlat1 = PI * double(ilat+1) / double(nlat);
    double mlng0 = PI*2 * (double(nlng/2 - ilng-1) / double(nlng)) - PI;
    double mlng1 = PI*2 * (double(nlng/2 - ilng) / double(nlng)) - PI;

//    vObject *vobj = mgr->getVisualObject();
//	double   rad = vobj->getObject()->getRadius();
	double   rad, erad;

    double slng, clng;
    double slat, clat;
	double lng, lat;
    double tu, tv, du, dv;
    double tur, tvr;
    vec3d_t pos, nml;

    int      vidx;
    int      nVertices;
    int      nIndices, nIndices1;

    vtxd_t   *vtx;
    uint16_t *idx, *pidx;

    nVertices = (grids+1)*(grids+1);
    nIndices  = 6 * (grids*grids);
    vtx       = new vtxd_t[nVertices];
    idx       = new uint16_t[nIndices];

//    int      nTexCoords;
//    double *vtxs, *nmls;
//	double *pvtx, *pnml;
//    double   *tc, *ptc;
//    nVertices   = 3 * ((grids+1)*(grids+1));
//    nTexCoords  = 2 * ((grids+1)*(grids+1));
//    vtxs  = new double[nVertices];
//    nmls  = new double[nVertices];
//    tc    = new double[nTexCoords];
//    pvtx  = vtxs;
//    pnml  = nmls;
//    ptc   = tc;

    if (mlng0 < PI*2)
        mlng0 += PI*2;
    if (mlng1 < PI*2)
        mlng1 += PI*2;

//	std::cout << std::fixed << std::setprecision(10);
//	std::cout << "----------------------" << std::endl;
//	std::cout << "LOD:  " << lod << " nLAT: " << nlat << " nLNG: " << nlng
//			  << " Grids: " << grids << std::endl;
//	std::cout << "iLAT: " << ilat << " iLNG: " << ilng << std::endl;
//	std::cout << "Latitude Range:  " << toDegrees(mlat0) << " to " << toDegrees(mlat1) << std::endl;
//	std::cout << "Longitude Range: " << toDegrees(mlng0) << " to " << toDegrees(mlng1) << std::endl;

//	std::cout << "Delta Angle: " << dang << " U:" << du << std::endl;
//	std::cout << "Alpha: " << alpha << std::endl;

    du  = (mlng1 - mlng0) / grids;
    dv  = (mlat1 - mlat0) / grids;
    tur = tcr.tumax - tcr.tumin;
    tvr = tcr.tvmax - tcr.tvmin;

    vidx = 0;
	for (int y = 0; y <= grids; y++)
	{
		lat  = mlat0 + (mlat1-mlat0) * ((double)y/(double)grids);
		slat = sin(lat); clat = cos(lat);
        tv = tcr.tvmin + tvr * (double(y)/double(grids));

//        std::cout << "Y = " << y << " LAT: " << toDegrees(lat) << std::endl;

		for (int x = 0; x <= grids; x++)
		{
			lng  = mlng0 + (mlng1-mlng0) * ((double)x/(double)grids);
			slng = sin(lng); clng = cos(lng);
            tu = 1 - (tcr.tumin + tur * (double(x)/double(grids)));

//            std::cout << "X = " << x << " LNG: " << toDegrees(lng) << std::endl;

//            pos = vec3d_t(axes.x()*slat*clng, axes.y()*clat, axes.z()*slat*slng);
//            nml = pos.normalized();

//            erad = rad + elevGlobe;
			erad = 1;
//            if (elev != nullptr) {
//            	int16_t edata = elev[(y+1)*ELEV_STRIDE + (x+1)];
//            	erad += (double(edata) * elevScale) / 1000.0;
//            	if (edata != 0)
//            		std::cout << "Elev X: " << x << " Y: " << y
//						      << "Elev: " << edata << std::endl;
//            }
//            else
//            	std::cout << "No elevation data for sphere..." << std::endl;

            nml = vec3d_t(slat*clng, clat, slat*slng);

            pos = nml * erad;

            vtx[vidx].vx = pos.x;
            vtx[vidx].vy = pos.y;
            vtx[vidx].vz = pos.z;

            vtx[vidx].nx = nml.x;
            vtx[vidx].ny = nml.y;
            vtx[vidx].nz = nml.z;

            vtx[vidx].tu = tu;
            vtx[vidx].tv = tv;

            vidx++;

//			std::cout << "(" << x << "," << y << "): " << lng0 << " " << lat0 << " --> ";
//			std::cout << "(" << nml0.x() << "," << nml0.y() << "," << nml0.z() << ")" << std::endl;
		}
//		std::cout << std::endl;
//		std::cout << "Actual: " << pvtx - vtxs << " Total: " << nvtx << std::endl;
//		std::cout << "Estimate: " << (grids+1)*2*(grids-1)+2 << std::endl;

		// Degenerate triangles to connect
//		pvtx[0] = pvtx[3] = pvtx[-3];
//		pvtx[1] = pvtx[4] = pvtx[-2];
//		pvtx[2] = pvtx[5] = pvtx[-1];
//
//		pnml[0] = pnml[3] = pnml[-3];
//		pnml[1] = pnml[4] = pnml[-2];
//		pnml[2] = pnml[5] = pnml[-1];

	}
//	std::cout << "Vertices: Actual: " << vidx << " Expect: " << nVertices1 << std::endl;

    nIndices1 = 0;
    pidx = idx;
    for (int y = 0; y < grids; y++) {
        for (int x = 0; x < grids; x++) {
            *pidx++ = (y+0)*(grids+1) + (x+0);
            *pidx++ = (y+0)*(grids+1) + (x+1);
            *pidx++ = (y+1)*(grids+1) + (x+0);

            *pidx++ = (y+1)*(grids+1) + (x+0);
            *pidx++ = (y+0)*(grids+1) + (x+1);
            *pidx++ = (y+1)*(grids+1) + (x+1);

//            std::cout << "Index: (" << pidx[0] << "," << pidx[1] << "," << pidx[2] << ")" << std::endl;
//            std::cout << "Index: (" << pidx[3] << "," << pidx[4] << "," << pidx[5] << ")" << std::endl;
//
//            pidx += 6;
            nIndices1 += 6;
        }
    }

    return glMesh::create(vidx, vtx, nIndices, idx);
}

/*
 * terrainmgr.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/render/terrainmgr.h"
#include "engine/render/gl/mesh.h"

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
: QuadTile(lod, ilat, ilng),
  mesh(nullptr)
{

}

TerrainTile::~TerrainTile()
{
	if (mesh != nullptr)
		delete mesh;
}

int TerrainTile::load()
{

	mesh = glMesh::createSphere(32, 32, lod, ilat, ilng);

	return 0;
}

void TerrainTile::paint()
{
	if (mesh != nullptr)
		mesh->paint();
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

void TerrainManager::paint()
{

	// Render the terrain
	for (int idx = 0; idx < 2; idx++)
		terrain[idx]->paint();
}

// Create spherical patch/hemisphere for LOD level 0+
//glMesh *TerrainManager::createSpherePatch(int lod, int ilat, int ilng, int grids,
//	tcRange2 &tcr, const int16_t *elev, double elevGlobe, double elevScale)
glMesh *createSpherePatch(int lod, int ilat, int ilng, int grids)
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
//    tur = tcr.tumax - tcr.tumin;
//    tvr = tcr.tvmax - tcr.tvmin;

    vidx = 0;
	for (int y = 0; y <= grids; y++)
	{
		lat  = mlat0 + (mlat1-mlat0) * ((double)y/(double)grids);
		slat = sin(lat); clat = cos(lat);
//        tv = double(y)/double(grids);
//        tv = tcr.tvmin + tvr * (double(y)/double(grids));

//        std::cout << "Y = " << y << " LAT: " << toDegrees(lat) << std::endl;

		for (int x = 0; x <= grids; x++)
		{
			lng  = mlng0 + (mlng1-mlng0) * ((double)x/(double)grids);
			slng = sin(lng); clng = cos(lng);
//            tu = 1 - (double(x)/double(grids));
//            tu = 1 - (tcr.tumin + tur * (double(x)/double(grids)));

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
//            nml = vec3d_t(slat*clng, slat*slng, clat);

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
            *pidx++ = (y+1)*(grids+1) + (x+0);
            *pidx++ = (y+0)*(grids+1) + (x+1);

            *pidx++ = (y+1)*(grids+1) + (x+0);
            *pidx++ = (y+1)*(grids+1) + (x+1);
            *pidx++ = (y+0)*(grids+1) + (x+1);

//            std::cout << "Index: (" << pidx[0] << "," << pidx[1] << "," << pidx[2] << ")" << std::endl;
//            std::cout << "Index: (" << pidx[3] << "," << pidx[4] << "," << pidx[5] << ")" << std::endl;
//
//            pidx += 6;
            nIndices1 += 6;
        }
    }

    return glMesh::create(vidx, vtx, nIndices, idx);
}

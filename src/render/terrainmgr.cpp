/*
 * terrainmgr.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/object.h"
#include "engine/player.h"
#include "render/vobject.h"
#include "render/texture.h"
#include "render/gl/context.h"
#include "render/gl/mesh.h"
#include "render/gl/scene.h"
#include "render/gl/shadermgr.h"
#include "render/terrainmgr.h"
#include "render/ztreemgr.h"
#include "util/dds.h"

static tcrd_t fullRange = { 0.0, 1.0, 0.0, 1.0 };

QuadTile::QuadTile(TerrainManager *_mgr, int _lod, int _ilat, int _ilng)
: mgr(_mgr), lod(_lod), ilat(_ilat), ilng(_ilng)
{
}

QuadTile::~QuadTile()
{
}


TerrainTile::TerrainTile(TerrainManager *mgr, int lod, int ilat, int ilng)
: QuadTile(mgr, lod, ilat, ilng),
  mesh(nullptr), scene(dynamic_cast<glScene *>(mgr->scene)),
  state(Invalid), txRange(fullRange)
{
}

TerrainTile::~TerrainTile()
{
	if (mesh != nullptr)
		delete mesh;
	if (txImage != nullptr && txOwn == true)
		delete txImage;
}

vec3d_t TerrainTile::center() const
{
	int nlat = 1 << lod;
	int nlng = 2 << lod;

	double latc = (PI/2) - PI * ((double(ilat)+0.5) / double(nlat));
	double lngc = (PI*2) * ((double(nlng/2 - ilng-1)+0.5) / double(nlng)) - PI;
    if (lngc < PI*2)
        lngc += PI*2;

	double slat = sin(latc), clat = cos(latc);
	double slng = sin(lngc), clng = cos(lngc);

	//	std::cout << "Index:  (" << lat << "," << lng << ") of (" << nlat << "," << nlng
	//              << ") at LOD " << lod+4 << std::endl;
	//	std::cout << "Center: (" << toDegrees(latc)
	//			  << "," << toDegrees(lngc) << ")" << std::endl;

	return vec3d_t(clat*clng, slat, clat*-slng);
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
	Texture  *image = nullptr;
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
//        txImage = mgr->scene->createTexture(image);
    	txImage = image;
    	txOwn   = true;
//        std::cout << "Texture created" << std::endl;
    }

	mesh = mgr->createSpherePatch(lod, ilat, ilng, 32, txRange);
	if (mesh != nullptr)
		mesh->txImage = txImage;
//	state = Inactive;
	return 0;
}

void TerrainTile::render(RenderParm &prm)
{
	if (mesh != nullptr)
		mesh->paint(scene->getContext());
}

// ************************************************************

TerrainManager::TerrainManager(vPlanet *vobj)
: scene(vobj->getScene()), vobj(vobj)
{
	string pname;

	pname = vobj->object()->getFolder() + "/ztree";

	// Initailize ztree database for tile image loading
	for (int idx = 0; idx < 4; idx++)
		ztree[idx] = nullptr;
	ztree[0] = zTreeManager::create(pname, "surf");

	pkg = dynamic_cast<glShaderPackage *>(scene->getShaderManager()->createShader("planet"));
	if (pkg != nullptr)
		pkg->initParams();

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

void TerrainManager::setRenderParm(RenderParm &prm, const mat4f_t &mvp)
{
	const Object *planet = vobj->object();
	const Player *player = scene->getPlayer();

	Camera *cam = player->getCamera(0);
	double  jdTime = scene->getTime();
	double  rad;
    double  lat, lng;
    vec3d_t cpos;

	prm.maxLOD = 20;
//    prm.lodBias = scn->getLODBias();
//
	prm.prot  = glm::toMat3(planet->rotation(jdTime));
	prm.ppos  = planet->position(jdTime);
	rad       = planet->radius();
    cpos      = cam->getPosition();
//
//	// Calculate camera position in planet frame.
	prm.cpos  = prm.ppos - cpos;
	prm.cdir  = glm::transpose(prm.prot) * -prm.cpos;
	prm.cdist = glm::length(prm.cdir);

////	prm.viewap = acos(1.0 / std::max(1.0, (prm.cdist/rad)));
	prm.viewap = (prm.cdist >= rad) ? acos(rad / prm.cdist) : 0;
//	prm.tanap  = cam->getTanAp();
//
////	std::cout << "Tile Manger - Render Parameter" << std::endl;
////	std::cout << "Planet Radius:    " << rad << std::endl;
////	std::cout << "Planet Position:  (" << prm.ppos.x() << "," << prm.ppos.y() << "," << prm.ppos.z() << ")" << std::endl;
////	std::cout << "Camera Position:  (" << prm.cpos.x() << "," << prm.cpos.y() << "," << prm.cpos.z() << ")" << std::endl;
////	std::cout << "Camera Direction: (" << prm.cdir.x() << "," << prm.cdir.y() << "," << prm.cdir.z() << ")" << std::endl;
////	std::cout << "Camera Distance:  " << prm.cdist << std::endl;
////	std::cout << "Horizon View:     " << toDegrees(prm.viewap) << std::endl;
////    std::cout << "Camera Position:  (" << cpos.x() << "," << cpos.y() << "," << cpos.z()
////              << ") in Universe frame" << std::endl;
//
////    obj->getCoordinates(prm.cpos, &lat, &lng);
////    std::cout << "Planet Position:  (" << toDegrees(lat) << "," << toDegrees(lng) << ")" << std::endl;
//
	prm.cdist /= rad;
	prm.cdir = glm::normalize(prm.cdir);
//
////	mat4d_t vmat = cam->getRotation().matrix();
//
////	prm.pvmat = pmat * vmat;

	prm.pkg = pkg;
}

void TerrainManager::process(TerrainTile *tile, RenderParm &prm)
{

	int lod  = tile->lod;
	int nlat = 1 << tile->ilat;
	int nlng = 2 << tile->ilng;

	double trad0 = sqrt(2.0)*(PI/2);
	double trad, alpha, adist;
	double erad;
	double tdist, apr;
	int    tlod;
	bool   split = false;
    int    bias = 4;

	tile->state = TerrainTile::Rendering;

//	// Find angle between camera and tile center.
//	trad  = trad0 / (double)nlat;
//	alpha = acos(glm::dot(prm.cdir, tile->cnt));
//	adist = alpha - trad;
//
//	// Check if tile is visible from camera position
//	// If tile is hiding from camera position, mark
//	// tile as invisible (LOD level 1+).
//	if (adist >= prm.viewap) {
////		std::cout << "Out of view: " << toDegrees(adist) << " >= " << toDegrees(prm.viewap) << std::endl;
//        tile->state = Tile::Invisible;
//        return;
//	}
//
//	// Check if tile is visible in view
//
//
//	// Check LOD level from tile distance
//	{
////		erad = obj->getObject()->getRadius();
//		erad = 1.0;
//		if (adist < 0.0) {
//			tdist = prm.cdist - erad;
////            std::cout << "*** Above tile (LOD " << tile->lod+4 << "," << tile->lat << "," << tile->lng << ")"
////                      << std::endl;
//		} else {
//			double h = erad * sin(adist);
//			double a = prm.cdist - (erad * cos(adist));
//			tdist = sqrt(h*h + a*a);
//		}
//        bias -= 2.0 * sqrt(std::max(0.0, adist) / prm.viewap);
//		apr = tdist * prm.tanap;
//		if (apr > 0.000001)
//			tlod = std::max(0, std::min(prm.maxLOD, (int)(bias - log(apr)*1.1)));
//		else
//			tlod = prm.maxLOD;
//        tlod += prm.lodBias;
//		split = (lod < tlod+1);
//	}
//
////    split = false;
//	if (split == true) {
////        std::cout << "Tile split at LOD " << lod+4 << "(Expected LOD " << tlod+4 << ")" << std::endl;
//        bool valid = true;
//        // Check children that have valid flag
//		for (int idx = 0; idx < 4; idx++) {
//			Tile *child = tile->getChild(idx);
//			if (child == nullptr)
//				child = createChildNode(tile, idx);
//			else if (child->state == Tile::Invalid)
//				loader->queue(child);
//            if ((child->state & TILE_VALID) == 0)
//                valid = false;
//		}
//        // When all children have valid flags, process nodes in next LOD level.
//        if (valid) {
//            tile->state = Tile::Active;
//            for (int idx = 0; idx < 4; idx++)
//                processNode(tile->getChild(idx), prm);
//        }
//	} else {
////		std::cout << "Tile LOD Level: " << lod+4 << " (" << tile->lat << ","
////				  << tile->lng << ")" << std::endl;
////		std::cout << "Alpha: " << toDegrees(alpha) << " Distance: " << toDegrees(adist)
////				<< " Tile Distance: " << tdist << std::endl;
////		std::cout << "Aperture: " << apr << " LOD: " << lod+4
////				<< " Tile Center LOD: " << tlod+4 << std::endl;
//	}

}

void TerrainManager::render(TerrainTile *tile, RenderParm &prm)
{

	if (tile->state == TerrainTile::Rendering)
		tile->render(prm);
//	else if (tile->state == TerrainTfile::Active)
//	{
//		for (int idx = 0; idx < 4; idx++) {
//			TerrainTile *child = tile->getChild(idx);
//			if (child != nullptr && (child->state & TILE_ACTIVE))
//				render(child);
//		}
//	}
}

void TerrainManager::render(const mat4f_t &mvp)
{
	RenderParm prm;

	setRenderParm(prm, mvp);

	pkg->use();
	pkg->mvp = mvp;
	pkg->setSamplerParam("tex") = 0;

	// Rendering terrain area
	for (int idx = 0; idx < 2; idx++)
		process(terrain[idx], prm);
	for (int idx = 0; idx < 2; idx++)
		render(terrain[idx], prm);
}

// Create spherical patch/hemisphere for LOD level 0+
//glMesh *TerrainManager::createSpherePatch(int lod, int ilat, int ilng, int grids,
//	tcRange2 &tcr, const int16_t *elev, double elevGlobe, double elevScale)
glMesh *TerrainManager::createSpherePatch(int lod, int ilat, int ilng,
		int grids, tcrd_t &tcr)
{
	int nlat = 1 << lod;
	int nlng = 2 << lod;

	float mlat0 = PI * float(ilat) / float(nlat);
	float mlat1 = PI * float(ilat+1) / float(nlat);
    float mlng0 = PI*2 * (float(nlng/2 - ilng-1) / float(nlng)) - PI;
    float mlng1 = PI*2 * (float(nlng/2 - ilng) / float(nlng)) - PI;

//    vObject *vobj = mgr->getVisualObject();
//	float   rad = vobj->getObject()->getRadius();
	float   rad, erad;

    float slng, clng;
    float slat, clat;
	float lng, lat;
    float tu, tv, du, dv;
    float tur, tvr;
    vec3f_t pos, nml;

    int      vidx;
    int      nVertices;
    int      nIndices, nIndices1;

    vtxf_t   *vtx;
    uint16_t *idx, *pidx;

    nVertices = (grids+1)*(grids+1);
    nIndices  = 6 * (grids*grids);
    vtx       = new vtxf_t[nVertices];
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
		lat  = mlat0 + (mlat1-mlat0) * (float(y)/float(grids));
		slat = sin(lat); clat = cos(lat);
        tv = tcr.tvmin + tvr * (float(y)/float(grids));

//        std::cout << "Y = " << y << " LAT: " << toDegrees(lat) << std::endl;

		for (int x = 0; x <= grids; x++)
		{
			lng  = mlng0 + (mlng1-mlng0) * (float(x)/float(grids));
			slng = sin(lng); clng = cos(lng);
            tu   = tcr.tumin + tur * (float(x)/float(grids));

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

            nml = vec3f_t(slat*clng, clat, slat*-slng);

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

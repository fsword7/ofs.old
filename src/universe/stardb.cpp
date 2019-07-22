/*
 * stardb.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/object.h"
#include "universe/astro.h"
#include "universe/star.h"
#include "universe/stardb.h"
#include "universe/startree.h"

#include "universe/hygdata.h"
#include "universe/xhipdata.h"

using namespace std;

StarDatabase::StarDatabase()
{
	unsortedStars.clear();
}

StarDatabase::~StarDatabase()
{
	unsortedStars.clear();
}

bool StarDatabase::loadHYGData(const std::string& fname)
{
	std::ifstream  data(fname.c_str(), std::ios::in);
	std::string    line;
	int            lineno;
//	int            cname;
	int            id, hip, hd, hr;
	float          ra, de, dist;
	float          ci, lum;
    float          bMag, vMag;
    char           spType[26];
	CelestialStar *star;

	if (!data.is_open())
	{
		std::cerr << "I/O Error: file '" << fname << "': "
				  << std::strerror(errno) << std::endl;
		return false;
	}

	lineno = 0;
//	cname = 0;
	while (std::getline(data, line))
	{
		std::stringstream lineStream(line);
		std::string       cell;
		std::vector<std::string> cells;

		if (lineno++ == 0)
			continue;
		cells.clear();
		while(std::getline(lineStream, cell, ','))
			cells.push_back(cell);

//		if (lineno < 100)
//			for (uint32_t idx = 0; idx < cells.size(); idx++)
//				std::cout << cells[idx] << ((idx < cells.size() - 1) ? "," : "\n");

//		if (!cells[HYG3_nNAME].empty()) {
//			std::cout << "HYG " << cells[HYG3_nID] << ": " << cells[HYG3_nNAME] << std::endl;
//			cname++;
//		}

		sscanf(cells[HYG3_nID].c_str(), "%d", &id);
		sscanf(cells[HYG3_nRA].c_str(), "%f", &ra);
		sscanf(cells[HYG3_nDEC].c_str(), "%f", &de);
		sscanf(cells[HYG3_nDIST].c_str(), "%f", &dist);
        sscanf(cells[HYG3_nAPPMAG].c_str(), "%f", &vMag);
		sscanf(cells[HYG3_nCI].c_str(), "%f", &ci);
		sscanf(cells[HYG3_nLUM].c_str(), "%f", &lum);
        sscanf(cells[HYG3_nSPECT].c_str(), "%s", spType);

//		std::cout << "ID: " << id << " RA: " << ra << " DEC: " << dec << " PLX: " << dist << std::endl;

		star = CelestialStar::create(ra, de, dist, spType, vMag, ci, lum);
		unsortedStars.push_back(star);
	}

	data.close();
//	std::cout << cname << " named stars" << std::endl;

    finish();

	return false;
}

bool StarDatabase::loadXHIPData(const std::string& pname)
{
	std::string    mfname = pname + "/main.dat";
	std::string    pfname = pname + "/photo.dat";
	std::string    bfname = pname + "/biblio.dat";
	std::string    gfname = pname + "/groups.dat";

	std::ifstream  mdata(mfname.c_str(), std::ios::in);
	std::ifstream  pdata(pfname.c_str(), std::ios::in);
	std::ifstream  bdata(bfname.c_str(), std::ios::in);
//	std::ifstream  gdata(gfname.c_str(), std::ios::in);

	std::string mline, pline, bline;
	int    lineno;
	int    hip, phip, bhip;
	int    hd;
	double ra, de, plx, eplx, dist, edist;
    double bMag, vMag, ci, lum;
	int    cnplx, czplx;
    char   spType[26];
    CelestialStar *star;

//    char *dir = getcwd(NULL, 0);
//    std::cerr << "Current directory: " << dir << std::endl;


    if (!mdata.is_open())
	{
		std::cerr << "I/O Error: file '" << mfname << "': "
				  << std::strerror(errno) << std::endl;
		return false;
	}

	if (!pdata.is_open())
	{
		std::cerr << "I/O Error: file '" << pfname << "': "
				  << std::strerror(errno) << std::endl;
		mdata.close();
		return false;
	}

	if (!bdata.is_open())
	{
		std::cerr << "I/O Error: file '" << bfname << "': "
				  << std::strerror(errno) << std::endl;
		mdata.close();
		pdata.close();
		return false;
	}

    // Create the Sun (Sol)
	star = CelestialStar::createSun();
	unsortedStars.push_back(star);

	lineno = 0;
	cnplx = 0;
	czplx = 0;
//	cname = 0;
	while (std::getline(mdata, mline) &&
		   std::getline(pdata, pline) &&
		   std::getline(bdata, bline))
	{
		std::stringstream mlStream(mline);
		std::stringstream plStream(pline);
		std::stringstream blStream(bline);

		std::string       cell;
		std::vector<std::string> mcells, pcells, bcells;

		lineno++;

		mcells.clear();
		pcells.clear();
		bcells.clear();
		while(std::getline(mlStream, cell, '|'))
			mcells.push_back(cell);
		while(std::getline(plStream, cell, '|'))
			pcells.push_back(cell);
		while(std::getline(blStream, cell, '|'))
			bcells.push_back(cell);

//		if (lineno < 100)
//			for (uint32_t idx = 0; idx < cells.size(); idx++)
//				std::cout << cells[idx] << ((idx < cells.size() - 1) ? "," : "\n");

//		if (!cells[HYG3_nNAME].empty()) {
//			std::cout << "HYG " << cells[HYG3_nID] << ": " << cells[HYG3_nNAME] << std::endl;
//			cname++;
//		}

		sscanf(mcells[XHIP_M_nHIP].c_str(), "%d", &hip);
		sscanf(pcells[XHIP_P_nHIP].c_str(), "%d", &phip);
		sscanf(bcells[XHIP_B_nHIP].c_str(), "%d", &bhip);
//		if (hip != phip || hip != bhip)
//			continue;
		if (hip != phip || hip != bhip) {
			std::cout << "HIP " << hip << " != " << phip << std::endl;
			break;
		}

		sscanf(mcells[XHIP_M_nRADEG].c_str(), "%lf", &ra);
		sscanf(mcells[XHIP_M_nDEDEG].c_str(), "%lf", &de);
		sscanf(mcells[XHIP_M_nPLX].c_str(), "%lf", &plx);
//		sscanf(mcells[XHIP_M_nDIST].c_str(), "%lf", &dist);
        sscanf(mcells[XHIP_M_nSPTYPE].c_str(), "%s", spType);

        sscanf(pcells[XHIP_P_nVAPPMAG].c_str(), "%lf", &vMag);
        if (sscanf(pcells[XHIP_P_nBAPPMAG].c_str(), "%lf", &bMag) != 1)
            bMag = vMag;
        ci = bMag - vMag;

//		sscanf(pcells[XHIP_P_nBV].c_str(), "%lf", &ci);
		sscanf(pcells[XHIP_P_nLUM].c_str(), "%lf", &lum);

		if (plx < 0) {
			cnplx++;
//			std::cout << "ID: " << hip << " RA: " << ra << " DEC: " << de << " PLX: " << plx << std::endl;
            dist = 100000;
		} else if (plx == 0.0) {
			czplx++;
//			std::cout << "ID: " << hip << " RA: " << ra << " DEC: " << de << " PLX: " << plx << std::endl;
            dist = 100000;
		} else {
//			sscanf(mcells[XHIP_M_nEPLX].c_str(), "%lf", &eplx);
			dist  = 1000.0/plx;
//			edist = 1000.0/plx * (1 + 1.2*(eplx/plx)*(eplx/plx));
//			std::cout << "ID: " << hip << " PLX: " << plx << " ePLX: " << eplx
//					  << " Dist: " << dist << " eDist: " << edist << std::endl;
		}

		star = CelestialStar::create(ra, de, dist, spType, vMag, ci, lum);
		unsortedStars.push_back(star);
	}

	mdata.close();
	pdata.close();
	bdata.close();
//	gdata.close();

	std::cout << "Total " << cnplx << " stars with negative parallax." << std::endl;
	std::cout << "Total " << czplx << " stars with zero parallax." << std::endl;

    finish();

	return false;
}

void StarDatabase::initStarOctreeData(std::vector<CelestialStar*> stars)
{
	double absMag = astro::convertAppToAbsMag(STARTREE_MAGNITUDE,
			STARTREE_ROOTSIZE * sqrt(3.0));

//	std::cout << "Star Tree: " << absMag << " magnitude" << std::endl;

	starTree = new StarTree(vec3d_t(1000.0, 1000.0, 1000.0), absMag);
	for (int idx = 0; idx < unsortedStars.size(); idx++)
		starTree->insert(*unsortedStars[idx], STARTREE_ROOTSIZE);

	std::cout << "Star Database has " << starTree->countNodes() << " nodes and "
			  << starTree->countObjects() << " objects" << std::endl;
}

void StarDatabase::finish()
{
	std::cout << "Total star count: " << unsortedStars.size() << std::endl;

	initStarOctreeData(unsortedStars);
}

CelestialStar *StarDatabase::find(const std::string& name) const
{
	for (int idx = 0; idx < unsortedStars.size(); idx++) {
		CelestialStar *star = unsortedStars[idx];
		if (star->name() == name)
			return star;
	}
	return nullptr;
}

//void StarDatabase::findVisibleStars(const ofsHandler& handle, const Player& player,
//		double faintestMag)
//{
//	vec3d_t vpos = player.getPosition();
//	double brightestMag = 1000.0;
//
//	for (uint32_t idx = 0; idx < uStars.size(); idx++) {
//		CelestialStar *star = uStars[idx];
//		vec3d_t spos = star->getPosition(0);
//		double  dist = (spos - vpos).norm();
//		double  appMag = star->getAppMag(convertKilometerToParsec(dist));
//
////		std::cout << "Star ID: " << idx << " Apparent Mag: " << appMag << " Distance: " << dist << std::endl;
//
////		if (appMag < brightestMag)
////			brightestMag = appMag;
//
//		if (appMag < faintestMag)
//			handle.process(*star, dist, appMag);
//	}
////	std::cout << "%%% Brightest Magnitude = " << brightestMag << std::endl;
//}
//
//int StarDatabase::findNearStars(const vec3d_t& obs, double mdist,
//		vector<const CelestialStar *>& stars) const
//{
////	double dist = astro::convertKilometerToParsec(mdist);
//
//	stars.clear();
//	for (int idx = 0; idx < uStars.size(); idx++) {
//		CelestialStar *star = uStars[idx];
//		double dist = (obs - star->getPosition(0)).norm();
//		if (dist < mdist)
//			stars.push_back(star);
//	}
//
//	return stars.size();
//}

void StarDatabase::findVisibleStars(const ofsHandler& handle, const vec3d_t& obs,
		const quatd_t &rot, double fov, double aspect, double limitMag) const
{
	planed_t frustum[5];
	vec3d_t  plane[5];

	mat3d_t  mrot = glm::toMat3(rot);
	double   h    = tan(fov / 2.0);
	double   w    = h * aspect;

	plane[0] = vec3d_t(0.0, 1.0, -h);
	plane[1] = vec3d_t(0.0, -1.0, -h);
	plane[2] = vec3d_t(1.0, 0.0, -w);
	plane[3] = vec3d_t(-1.0, 0.0, -w);
	plane[4] = vec3d_t(0.0, 0.0, -1.0);

	for (int idx = 0; idx < 5; idx++) {
		plane[idx] = glm::transpose(mrot) * glm::normalize(plane[idx]);
		frustum[idx] = planed_t(plane[idx], obs);
	}

//	std::cout << "Find visible stars by using octree..." << std::endl;
	starTree->processVisibleStars(handle, obs, frustum, limitMag, STARTREE_ROOTSIZE);
}

void StarDatabase::findNearStars(const ofsHandler& handle, const vec3d_t& obs,
		double radius) const
{
	starTree->processNearStars(handle, obs, radius, STARTREE_ROOTSIZE);
}

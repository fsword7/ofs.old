/*
 * mesh.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "engine/render/gl/mesh.h"

glMesh::glMesh()
{
}

glMesh::~glMesh()
{
}

void glMesh::createSphere(int glat, int glng)
{
	int nlat, ilat;
	int nlng, ilng;
	int lod;

	int nvtx = (glat+1)*(glng+1);

	double lat, clat, slat, lat0, lat1;
	double lng, clng, slng, lng0, lng1;

	lat0 = PI * (nlat/2 - ilat - 1)/nlat;
	lat1 = PI * (nlat/2 - ilat) / nlat;
	lng0 = 0;
	lng1 = (PI * 2) / nlng;

	double clat0 = cos(lat0), slat0 = sin(lat0);
	double clat1 = cos(lat1), slat1 = sin(lat1);
	double clng0 = cos(lng0), slng0 = sin(lng0);
	double clng1 = cos(lng1), slng1 = sin(lng1);

	for (int y = 0; y < glat; y++) {
		for (int x = 0; x < glng; x++) {

		}
	}
}

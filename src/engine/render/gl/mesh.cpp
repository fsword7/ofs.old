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
: nvtx(0), vtx(nullptr),
  nidx(0), idx(nullptr)
{
}

glMesh::~glMesh()
{
	if (vtx != nullptr)
		delete [] vtx;
	if (idx != nullptr)
		delete [] idx;
}

void glMesh::paint()
{
	GLsizei stride = sizeof(vtxd_t);

	glColor4f(1, 1, 1, 1);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, stride, &vtx[0].px);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLE_STRIP, nidx, GL_UNSIGNED_SHORT, idx);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisableClientState(GL_VERTEX_ARRAY);
}

glMesh *glMesh::createSphere(int glat, int glng, int lod, int ilat, int ilng)
{
	int nlat  = lod << 1;
	int nlng  = lod << 2;
	int nvtx  = (glat+1)*(glng+1);
	int nvtxb = nvtx + (glat+1) + (glng+1);
	int nidx  = 2*glat*glng*3;

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

	vec3d_t nml, pos;

	vtx_t<double> *vtx = new vtx_t<double>[nvtxb];
	uint16_t *idx = new uint16_t[nidx];

	// Initialize vertexes
	int vidx = 0;
	for (int y = 0; y <= glat; y++) {
		lat = lat0 + (lat1-lat0) * (double(y)/double(glat));
		slat = sin(lat); clat = cos(lat);
		for (int x = 0; x <= glng; x++) {
			lng = lng0 + (lng1-lng0) * (double(x)/double(glng));
			slng = sin(lng); clng = cos(lng);

			nml = vec3d_t(clat*clng, slat, clat*slng);
			pos = nml;

			vtx[vidx].px = pos.x;
			vtx[vidx].py = pos.y;
			vtx[vidx].pz = pos.z;

			vtx[vidx].nx = nml.x;
			vtx[vidx].ny = nml.y;
			vtx[vidx].nz = nml.z;

			vtx[vidx].tu0 = 0;
			vtx[vidx].tv0 = 0;
			vidx++;
		}
	}

	// Initialize indices for vertexes
	int iidx  = 0;
	int nofs0 = 0;
	for (int y = 0; y < glat; y++) {
		int nofs1 = nofs0 + glng + 1;
		for (int x = 0; x < glng; x++) {
			idx[iidx++] = nofs0+x;
			idx[iidx++] = nofs1+x;
			idx[iidx++] = nofs0+x+1;
			idx[iidx++] = nofs1+x+1;
			idx[iidx++] = nofs0+x+1;
			idx[iidx++] = nofs1+x;
		}
		nofs0 = nofs1;
	}

	glMesh *mesh = new glMesh();

	mesh->nvtx = nvtx;
	mesh->nidx = nidx/3;
	mesh->vtx  = vtx;
	mesh->idx  = idx;

	return mesh;
}

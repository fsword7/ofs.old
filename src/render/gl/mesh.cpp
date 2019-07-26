/*
 * mesh.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "main/math.h"
#include "render/gl/texture.h"
#include "render/gl/mesh.h"

glMesh::glMesh()
: nvtx(0), vtx(nullptr),
  nidx(0), idx(nullptr),
  isAllocated(false),
  vbo(0), ibo(0)
{
}

glMesh::~glMesh()
{
	if (vtx != nullptr)
		delete [] vtx;
	if (idx != nullptr)
		delete [] idx;

	// Delete all VBO allocations
	if (ibo != 0)
		glDeleteBuffers(1, &ibo);
	if (vbo != 0)
		glDeleteBuffers(1, &vbo);
}

glMesh *glMesh::create(int nvtx, vtxd_t *vtx, int nidx, uint16_t *idx)
{
	glMesh *mesh = new glMesh();

	mesh->nvtx = nvtx;
	mesh->vtx  = vtx;
	mesh->nidx = nidx;
	mesh->idx  = idx;

	return mesh;
}

void glMesh::allocate()
{
	// Initialize vertex buffer objects
	if (vbo == 0) {
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vtxd_t)*nvtx, vtx, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (ibo == 0) {
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t)*nidx, idx, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	isAllocated = true;
}

void glMesh::paint()
{
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, sizeof(vtxd_t), &vtx[0].vx);

//	glEnableClientState(GL_NORMAL_ARRAY);
//	glNormalPointer(GL_DOUBLE, sizeof(vtxd_t), &vtx[0].nx);

	if (txImage != nullptr) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_TEXTURE_2D);
		glTexCoordPointer(2, GL_DOUBLE, sizeof(vtxd_t), &vtx[0].tu);

		txImage->bind();
	} else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawElements(GL_TRIANGLES, nidx, GL_UNSIGNED_SHORT, idx);

	if (txImage != nullptr) {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
	} else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisableClientState(GL_VERTEX_ARRAY);
//	glDisableClientState(GL_NORMAL_ARRAY);
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
	vec3d_t  *vpos = new vec3d_t[nvtxb];
	vec3d_t  *vnml = new vec3d_t[nvtxb];
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

			vtx[vidx].vx = pos.x;
			vtx[vidx].vy = pos.y;
			vtx[vidx].vz = pos.z;

			vtx[vidx].nx = nml.x;
			vtx[vidx].ny = nml.y;
			vtx[vidx].nz = nml.z;

			vpos[vidx].x = pos.x;
			vpos[vidx].y = pos.y;
			vpos[vidx].z = pos.z;

			vnml[vidx].x = nml.x;
			vnml[vidx].y = nml.y;
			vnml[vidx].z = nml.z;

			vtx[vidx].tu = 0;
			vtx[vidx].tv = 0;
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

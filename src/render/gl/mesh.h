/*
 * mesh.h
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "GL/glew.h"

class ImageTexture;

template<typename T>
struct vtx_t {
	T vx, vy, vz;
	T nx, ny, nz;
	T tu, tv;
};

typedef vtx_t<float>  vtxf_t;
typedef vtx_t<double> vtxd_t;

class glMesh
{
public:
	glMesh();
	~glMesh();

	static glMesh *create(int nvtx, vtxd_t *vtx, int nidx, uint16_t *idx);

	void allocate();
	void paint();

	static glMesh *createSphere(int glat, int glng, int lod, int ilat, int ilng);

public:
	int		 nvtx, nidx;
	vtxd_t   *vtx;
	uint16_t *idx;

	ImageTexture *txImage = nullptr;

private:
	bool   isAllocated;
	GLuint vbo, ibo;
};

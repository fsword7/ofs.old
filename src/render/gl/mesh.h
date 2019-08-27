/*
 * mesh.h
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "GL/glew.h"

class Texture;

template<typename T>
struct vtx_t {
	T vx, vy, vz;
	T nx, ny, nz;
	T tu, tv;
};

typedef vtx_t<float>  vtxf_t;
//typedef vtx_t<double> vtxd_t;

class glMesh
{
public:
	glMesh();
	~glMesh();

	static glMesh *create(int nvtx, vtxf_t *vtx, int nidx, uint16_t *idx);

	void allocate();
	void paint(const glContext *gl);

	static glMesh *createSphere(int glat, int glng, int lod, int ilat, int ilng);

public:
	int		 nvtx, nidx;
	vtxf_t   *vtx;
	uint16_t *idx;

	Texture *txImage = nullptr;

private:
	bool   isAllocated;
	GLuint vbo, ibo;
};

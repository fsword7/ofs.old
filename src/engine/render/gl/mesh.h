/*
 * mesh.h
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

template<class T>
struct vtx_t {
	T px, py, pz;
	T nx, ny, nz;
	T tu0, tv0;
};

typedef vtx_t<float>  vtxf_t;
typedef vtx_t<double> vtxd_t;

class glMesh
{
public:
	glMesh();
	~glMesh();

	void createSphere(int glat, int glng, int lod, int ilat, int ilng);
};

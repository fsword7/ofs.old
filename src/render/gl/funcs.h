/*
 * glfuncs.h
 *
 *  Created on: Nov 9, 2018
 *      Author: Tim Stark
 */

#pragma once

#include <GL/glew.h>

inline void glMatrix(const mat4d_t& m)
{
	mat4d_t trans = glm::transpose(m);
	glMultMatrixd(&trans[0].x);
}

template<class T>
inline void glFrustum(T fovy, T aspect, T near, T far)
{
	T fw, fh;

	fh = tan(fovy / 2.0) * near;
	fw = fh * aspect;

	glFrustum( -fw, fw, -fh, fh, near, far);
}

inline void glRotate(const quatd_t& q)
{
	glMatrix(glm::mat4_cast(q));
}

inline void glTranslate(const vec3d_t& v)
{
	glTranslated(v.x, v.y, v.z);
}

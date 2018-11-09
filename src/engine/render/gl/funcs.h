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
	glLoadMatrixd(&trans[0].x);
}

inline void glRotate(const quatd_t& q)
{
	glMatrix(glm::mat4_cast(q));
}

inline void glTranslate(const vec3d_t& v)
{
	glTranslated(v.x, v.y, v.z);
}

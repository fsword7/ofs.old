/*
 * math.h - Math OFS header
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#define PI (3.14159265358979323846)

typedef glm::dvec3 vec3d_t;
typedef glm::dquat quatd_t;

typedef glm::dmat3 mat3d_t;
typedef glm::dmat4 mat4d_t;


template<class T>
inline T toRadian(T deg) { return deg * (PI / 180.0); }

template<class T>
inline T toDegree(T rad) { return rad * (180.0 / PI); }

//quatd_t lookAt(vec3d_t from, vec3d_t to, vec3d_t up)
//{
//	mat3d_t m;
//
//	vec3d_t dir = glm::normalize(to - from);
//	vec3d_t v   = glm::normalize(glm::cross(dir, up));
//	vec3d_t u   = glm::cross(v, dir);
//
//	m[0] = v;
//	m[1] = u;
//	m[2] = -dir;
//
//	return glm::conjugate(glm::quat_cast(m));
//}

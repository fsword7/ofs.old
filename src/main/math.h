/*
 * math.h - Math OFS header
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

#include <cmath>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "main/plane.h"

#define PI (3.14159265358979323846)

typedef glm::tvec3<float> vec3f_t;
typedef glm::tvec4<float> vec4f_t;
typedef glm::tquat<float> quatf_t;

typedef glm::tvec3<double> vec3d_t;
typedef glm::tvec4<double> vec4d_t;
typedef glm::tquat<double> quatd_t;

typedef glm::dmat3 mat3d_t;
typedef glm::dmat4 mat4d_t;

#define square(val) ((val) * (val))
#define cube(val)   ((val) * (val) * (val))

template<class T>
inline T toRadian(T deg) { return deg * (PI / 180.0); }

template<class T>
inline T toDegree(T rad) { return rad * (180.0 / PI); }

template<class T> inline T clamp(T x)
{
	if (x < 0.0)
		return 0.0;
	else if (x > 1.0)
		return 1.0;
	else return x;
}

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

template <class T>
glm::tquat<T> xrot(T radians)
{
	T ang = radians * T(0.5); // half angle
	return glm::tquat<T>(std::cos(ang), std::sin(ang), 0, 0);
}

template <class T>
glm::tquat<T> yrot(T radians)
{
	T ang = radians * T(0.5); // half angle
	return glm::tquat<T>(std::cos(ang), 0, std::sin(ang), 0);
}

template <class T>
glm::tquat<T> zrot(T radians)
{
	T ang = radians * T(0.5); // half angle
	return glm::tquat<T>(std::cos(ang), 0, 0, std::sin(ang));
}

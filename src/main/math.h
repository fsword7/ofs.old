/*
 * math.h - Math OFS header
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define PI (3.14159265358979323846)

typedef glm::dvec3 vec3d_t;
typedef glm::dquat quatd_t;

template<class T>
inline T toRadian(T deg) { return deg * (PI / 180.0); }

template<class T>
inline T toDegree(T rad) { return rad * (180.0 / PI); }

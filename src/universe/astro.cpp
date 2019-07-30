/*
 * astro.cpp
 *
 *  Created on: Apr 4, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "engine/object.h"
#include "universe/star.h"
#include "universe/astro.h"

using namespace astro;

constexpr double astro::G = 6.673889e-11; // Official gravitational constant [N (m/kg)^2]

vec3d_t astro::convertEquatorialToEcliptic(double ra, double dec, double pc)
{
	double  theta, phi;
	double  x, y, z;
//	double  km = convertParsecToKilometer(pc);
	vec3d_t rot(-J2000Obliquity, 0, 0);

	theta = toRadian(ra) + PI;
	phi   = toRadian(dec - 90.0);

	x = sin(phi) * cos(theta);
	y = cos(phi);
	z = sin(phi) * -sin(theta);

	return glm::normalize(vec3d_t(x, y, z) * glm::dquat(rot)) * pc;
}




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

	theta = ra * PI*2.0 + PI;
	phi   = ((dec / 90.0) - 1.0) * PI/2.0;

	x = cos(theta) * sin(phi);
	y = cos(phi);
	z = -sin(theta) * sin(phi);

	return glm::normalize(vec3d_t(x, y, z) * glm::dquat(rot)) * pc;
}




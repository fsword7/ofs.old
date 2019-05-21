/*
 * star.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "universe/astro.h"
#include "universe/star.h"

//#include "main/math.h"
//#include "main/eigen.h"
//#include "engine/object.h"
//#include "engine/universe/astro.h"
//#include "engine/universe/body.h"
//#include "engine/universe/star.h"
//#include "engine/universe/solarsys.h"

CelestialStar::CelestialStar()
: Object(ObjectType::objCelestialStar),
  flags(0), lpos(0, 0, 0), ra(0.0), dec(0.0), plx(0.0),
  absMag(0.0), bMag(0.0), vMag(0.0),
  ci(0.0), lum(0.0), temp(0)
//  system(nullptr)
{

}

CelestialStar::CelestialStar(string& name)
: Object(name, ObjectType::objCelestialStar),
  flags(0), lpos(0, 0, 0), ra(0.0), dec(0.0), plx(0.0),
  absMag(0.0), bMag(0.0), vMag(0.0),
  ci(0.0), lum(0.0), temp(0)
//  system(nullptr)
{

}

CelestialStar::~CelestialStar()
{
}


double CelestialStar::getLuminosity() const
{
	return astro::convertAbsMagToLum(absMag);
}

int CelestialStar::getTemperature() const
{
	double ci = 0.92 * this->ci;

	return (int)(4600 * ((1 / (ci + 1.7)) + (1 / (ci + 0.62))));
}

double CelestialStar::getRadius() const
{
	if (flags & knownRadius)
		return radius;

	// Determine estimate star radius by using that formula
	// R/Rs = (Ts/T)^2 (L/Ls)^1/2
	return square(SOLAR_TEMPERATURE / getTemperature()) *
		sqrt(getLuminosity() / SOLAR_LUMINOSITY) *
		SOLAR_RADIUS;
}

//double CelestialStar::getRadius()
//{
//	if (flags & knownRadius)
//		return radius;
//
//	// Determine estimate star radius by using that formula
//	// R/Rs = (Ts/T)^2 (L/Ls)^1/2
//	return square(SOLAR_TEMPERATURE / getTemperature()) *
//		sqrt(getLuminosity() / SOLAR_LUMINOSITY) *
//		SOLAR_RADIUS;
//}

vec3d_t CelestialStar::getPosition(double) const
{
	return lpos;
}

//vec3d_t CelestialStar::getPosition(double)
//{
//	return lpos;
//}

double CelestialStar::getAppMag(double dist) const
{
	return astro::convertAbsToAppMag(absMag, dist);
}

//void CelestialStar::setSolarSystem(SolarSystem *sys)
//{
//	system = sys;
//}

CelestialStar *CelestialStar::create(double ra, double dec, double plx,
		const char *spType, double appMag, double ci, double lum)
{
	CelestialStar *star;
	double pc;
	int    temp;

	star = new CelestialStar();
	pc = 1000.0 / plx;
	star->lpos = astro::convertEquatorialToEcliptic(ra, dec, pc);

	temp = (int)(4600 * (1/((ci*0.92)+1.7) + 1/((ci*0.92)+0.62)));

	star->ra  = ra;
	star->dec = dec;
	star->plx = plx;
    star->absMag = astro::convertAppToAbsMag(appMag, pc);
    star->bMag = appMag + ci;
    star->vMag = appMag;
	star->ci  = ci;
	star->lum = lum;
	star->temp = temp;

	return star;
}

CelestialStar *CelestialStar::createSun()
{
	CelestialStar *star = new CelestialStar();

	star->setName("Sol");
	star->ra       = 0.0;
	star->dec      = 0.0;
	star->plx      = 0.0;
	star->absMag   = SOLAR_ABSMAG;
	star->bMag     = 0.0;
	star->vMag     = 0.0;
	star->ci       = SOLAR_CI;
	star->lum      = SOLAR_LUMINOSITY;
	star->temp     = SOLAR_TEMPERATURE;

	star->flags    = knownRadius;
	star->radius   = SOLAR_RADIUS;

	return star;
}

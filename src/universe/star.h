/*
 * star.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "engine/object.h"

//// default solar parameters (our sun)
////#define SOLAR_ABSMAG		4.83
////#define SOLAR_IRRADIANCE	1367.6
////#define SOLAR_POWER			3.8462e26
////#define SOLAR_LUMINOSITY	1.0
////#define SOLAR_TEMPERATURE	5777.0
////#define SOLAR_CI			0.656
////#define SOLAR_RADIUS		696000.0
////#define SOLAR_MASS			1.9885e30

enum SpectralClass
{
    Spectral_Unknown = 0,
    Spectral_O  = 1,
    Spectral_B  = 2,
    Spectral_A  = 3,
    Spectral_F  = 4,
    Spectral_G  = 5,
    Spectral_K  = 6,
    Spectral_M  = 7,
    Spectral_R  = 8,
    Spectral_S  = 9,
    Spectral_N  = 10,
    Spectral_WC = 11,
    Spectral_WN = 12,
    Spectral_L  = 13,
    Spectral_T  = 14,
    Spectral_C  = 15,
    Spectral_DA = 16,
    Spectral_DB = 17,
    Spectral_DC = 18,
    Spectral_DO = 19,
    Spectral_DQ = 20,
    Spectral_DZ = 21,
    Spectral_D  = 22,
    Spectral_DX = 23
};

class CelestialStar : public Object
{
public:
	enum {
		knownRadius   = 1,
		knownRotation = 2,
		knownSurface  = 4
	};

	CelestialStar();
	CelestialStar(string& name);
	~CelestialStar();

	int    getTemperature() const;
	double getLuminosity() const;
	double getRadius() const;
//	double getRadius();
	double getAppMag(double dist) const;

	inline double getAbsMag() const { return absMag; }
//	inline SolarSystem *getSolarSystem() const { return system; }

	vec3d_t getPosition(double tjd) const;
//	vec3d_t getPosition(double tjd);

//	void setSolarSystem(SolarSystem *sys);

	static CelestialStar *create(double ra, double dec, double plx, const char *spType,
								 double appMag, double ci, double lum);
	static CelestialStar *createSun();

private:
	// Star known flags
	uint32_t flags;

	// Star position/velocity
	vec3d_t  lpos;    // Local position
	double   ra, dec, plx;

	// Spectral class/type
	std::string  specName;
	std::string  specType;

	// Star atmosphere parameters
	double radius;
	double absMag;
	double bMag, vMag;
	double ci, lum;
	int    temp;

};

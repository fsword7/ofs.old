/*
 * object.h
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#pragma once

enum ObjectType {
	objUnknown = 0,
	objCelestialBody,
	objCelestialStar
};

class Object {
public:
	Object(string name, ObjectType type);
	~Object();

	inline ObjectType type() const { return objType; };
	inline double radius() const   { return objRadius; };
	inline double mass() const     { return objMass; };

	inline void setRadius(double rad) { objRadius = rad; }
	inline void setMass(double mass)  { objMass = mass; }

	string name(int idx = 0);

private:
	ObjectType objType;

protected:
	vector<string> objNames;

	double  objRadius;		// Object radius
	vec3d_t objSemiAxes;	// Object semi-axes
	double  objMass;		// Object mass
	double  objAlbedo;		// Object albedo

};

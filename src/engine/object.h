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

	string name(int idx = 0);

private:
	ObjectType objType;

	vector<string> objNames;
};

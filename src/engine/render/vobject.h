/*
 * vobject.h - visual object for rendering facility
 *
 *  Created on: Oct 15, 2018
 *      Author: Tim Stark
 */

#pragma once

class Object;
class TerrainManager;
class Scene;

class vObject {
public:
	vObject(const Object *obj, const Scene *scene);
	virtual ~vObject();

	virtual void paint() = 0;

protected:
	const Object *obj;
	const Scene  *scene;

private:

};

//class vStar : public vObject
//{
//public:
//	vStar();
//	~vStar();
//
//};

class vPlanet : public vObject
{
public:
	vPlanet(const Object *obj, const Scene *scene);
	~vPlanet();

	void paint();

private:
	TerrainManager *terrain;
};

/*
 * vobject.h - visual object for rendering facility
 *
 *  Created on: Oct 15, 2018
 *      Author: Tim Stark
 */

#pragma once

class Object;

class vObject {
public:
	vObject(Object *obj);
	~vObject();

protected:
	const Object *obj;

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
	vPlanet(Object *obj);
	~vPlanet();

};

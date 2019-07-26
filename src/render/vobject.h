/*
 * vobject.h - visual object for rendering facility
 *
 *  Created on: Oct 15, 2018
 *      Author: Tim Stark
 */

#pragma once

class Object;
class Player;
class TerrainManager;
class Scene;

class vObject {
public:
	vObject(Object *obj, Scene *scene);
	virtual ~vObject();

	Object *object() { return obj; }
	inline Scene *getScene() { return scene; }

	void update(Player &player);

	virtual void paint() = 0;

protected:
	Object *obj;
	Scene  *scene;

	bool	visible;	// visible object within camera view
	bool	point;		//   as point

	double	radius;		// object radius
	vec3d_t opos;		// object position
	vec3d_t	cpos;		// camera position from object relative
	double	cdist;		// camera distance from object center

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
	vPlanet(Object *obj, Scene *scene);
	~vPlanet();

	void paint();

private:
	TerrainManager *terrain;
};

/*
 * scene.h - Scene rendering facility
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "GL/glew.h"

class Player;
class Universe;
class vObject;

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void init(int w, int h) = 0;
	virtual void resize(int w, int h) = 0;
	virtual void paint(Player &player, Universe &universe) = 0;

protected:
	int    width, height;
	double aspect;
};

class glScene : public Scene {
public:
	glScene();
	~glScene();

	void init(int w, int h);
	void resize(int w, int h);
	void paint(Player &player, Universe &universe);

private:
	vObject *vobj;  // test - be removed later.
};

#define DIST_NEAR	0.001
#define DIST_FAR	1.0e9

/*
 * scene.h
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#pragma once

#include "GL/glew.h"
#include "render/scene.h"

class glScene : public Scene {
public:
	glScene();
	~glScene();

	void initStarVertex();

	void init(int w, int h);
	void resize(int w, int h);
	void paint(Player &player, Universe &universe);

private:
	vObject *vobj;  // test - be removed later.
};

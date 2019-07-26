/*
 * scene.h
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#pragma once

#include "GL/glew.h"
#include "render/scene.h"

class Image;
class ImageTexture;

class glScene : public Scene {
public:
	glScene();
	~glScene();

	void initStarVertex();

	ImageTexture *createTexture(Image *image);

	void init(int w, int h);
	void resize(int w, int h);
	void paint(Player &player, Universe &universe);

private:
	vObject *vobj;  // test - be removed later.
};

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
	void buildGaussianStarTexture(int log2size);

	ImageTexture *createTexture(Image *image);

	void init(int w, int h);
	void resize(int w, int h);
	void render(Player &player, Universe &universe);

	void renderStars(const StarDatabase &stardb, const Player &player, double faintest);

private:
	vObject *vobj;  // test - be removed later.
};

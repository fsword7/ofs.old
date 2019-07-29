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
class Constellations;

class glScene : public Scene {
public:
	glScene();
	~glScene();

	void initStarVertex();

	ImageTexture *createTexture(Image *image);

	void init(int w, int h);
	void resize(int w, int h);
	void render(Player &player, Universe &universe);

	void renderStars(const StarDatabase &stardb, const Player &player, double faintest);
	void renderConstellations(const Universe &universe, const Player &player);

private:
	vObject *vobj;  // test - be removed later.
};

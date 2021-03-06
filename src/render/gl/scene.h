/*
 * scene.h
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#pragma once

#include "GL/glew.h"
#include "render/gl/context.h"
#include "render/scene.h"

class Image;
class ImageTexture;
class Constellations;
class Texture;

class glScene : public Scene {
public:
	glScene();
	~glScene();

	void initStarVertex();

//	Texture *createTexture(int w, int h);

	void init(int w, int h);
	void resize(int w, int h);
	void render(Player &player, Universe &universe);

	void renderStars(const StarDatabase &stardb, const Player &player, double faintest);
	void renderConstellations(const Universe &universe, const Player &player);

	inline const glContext *getContext() const { return &gl; }

protected:

	void createStarTexture(uint8_t *data, int mip, int scale);
	void createGlareTexture(uint8_t *data, int mip, int scale);

	Texture *createStarTexture(int lod);
	Texture *createGlareTexture(int lod);

private:
	vObject *vobj;  // test - be removed later.

	glContext gl;

	Texture *starTexture = nullptr;
	Texture *glareTexture = nullptr;
};

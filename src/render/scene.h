/*
 * scene.h - Scene rendering facility
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#pragma once

class Player;
class Universe;
class vObject;
class CelestialStar;
class ShaderManager;
class StarRenderer;
class Image;
class ImageTexture;
class StarDatabase;
class Camera;

class Scene {
public:
	Scene();
	virtual ~Scene();

	ShaderManager *getShaderManager() const { return shader; }

	double calculatePixelSize(Camera *cam) const;

	virtual void renderStars(const StarDatabase &stardb, const Player &player, double faintest) = 0;
	virtual ImageTexture *createTexture(Image *image) = 0;

	virtual void init(int w, int h) = 0;
	virtual void resize(int w, int h) = 0;
	virtual void render(Player &player, Universe &universe) = 0;

protected:
	int    width, height;
	double aspect;

	std::vector<const CelestialStar *> closeStars;

	ShaderManager *shader = nullptr;
	StarRenderer  *starRenderer = nullptr;
};

#define DIST_NEAR	0.001
#define DIST_FAR	1.0e9

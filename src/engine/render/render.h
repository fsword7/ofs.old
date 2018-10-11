/*
 * render.h
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "GL/glew.h"

class Player;
class Universe;

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	virtual void init(int w, int h) = 0;
	virtual void resize(int w, int h) = 0;
	virtual void paint(Player &player, Universe &universe) = 0;

protected:
	int width, height;
};

class glRenderer : public Renderer {
public:
	glRenderer();
	~glRenderer();

	void init(int w, int h);
	void resize(int w, int h);
	void paint(Player &player, Universe &universe);
};

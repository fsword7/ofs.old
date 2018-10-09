/*
 * render.h
 *
 *  Created on: Oct 8, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "GL/glew.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	virtual void init(int w, int h) = 0;
	virtual void resize(int w, int h) = 0;
	virtual void paint() = 0;

protected:
	int width, height;
};

class glRenderer : public Renderer {
public:
	glRenderer();
	~glRenderer();

	void init(int w, int h);
	void resize(int w, int h);
	void paint();
};

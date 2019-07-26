/*
 * texture.h
 *
 *  Created on: Jul 26, 2019
 *      Author: Tim Stark
 */

#pragma once

#include <GL/glew.h>
#include "render/image.h"
#include "render/texture.h"

class glImageTexture : public ImageTexture
{
public:
	glImageTexture(Image *img) : ImageTexture(img) {}
	~glImageTexture();

	void load(Image *img, int target);
	void bind();

private:
	int glName = 0;
};

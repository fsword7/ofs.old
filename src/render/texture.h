/*
 * texture.h
 *
 *  Created on: Jul 23, 2019
 *      Author: Tim Stark
 */

#pragma once

class Texture
{
public:
	Texture(int w, int h, int d = 1)
	: width(w), height(h), depth(d),
	  format(0) {}
	virtual ~Texture() = default;

	virtual void bind() = 0;

protected:
	int width, height;
	int depth;
	int format;
};

class ImageTexture : public Texture
{
public:
	ImageTexture(Image *img)
	: Texture(img->getWidth(), img->getHeight()),
	  image(img), initFlag(false) {}
	virtual ~ImageTexture()
	{
		if (image != nullptr)
			delete image;
	}

	virtual void load(Image *img, int target) = 0;

protected:
	Image *image;
	bool   initFlag;
};

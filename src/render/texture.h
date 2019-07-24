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
	Texture(int w, int h, int d = 1);
	virtual ~Texture();

	virtual void bind() = 0;

protected:
	int width, height;
	int depth;
	int format;
};

class ImageTexture : public Texture
{
public:
	ImageTexture(Image *img);
	~ImageTexture();

private:
	Image *image;
	bool   initFlag;
};

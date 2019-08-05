/*
 * texture.cpp
 *
 *  Created on: Jul 28, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/texture.h"

Texture::Texture(int w, int h, int mips)
: width(w), height(h), depth(1), mipLevels(mips)
{
}

Texture::~Texture()
{
	if (data != nullptr)
		delete [] data;
}

int Texture::getMipDataSize(int lod) const
{
	if (lod >= mipLevels)
		return 0;
	return getMipSize(format, width, height, lod);
}

uint8_t *Texture::getMipData(int lod)
{
	if (lod >= mipLevels)
		return nullptr;

	int ofs = 0;
	for (int lod = 0; lod < mipLevels; lod++)
		ofs += getMipDataSize(lod);

	return data + ofs;
}

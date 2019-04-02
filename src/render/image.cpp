/*
 * image.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/image.h"
#include "render/gl/funcs.h"

Image::Image(int w, int h, int fmt, int mips)
: width(w), height(h), pitch(0),
  mipLevels(mips), format(fmt),
  data(nullptr)
{
	size = 0;
	for (int lod = 0; lod < mips; lod++)
		size += getMipLevelSize(w, h, lod, fmt);

	components = getComponents(fmt);
	data = new uint8_t[size];
}

Image::~Image()
{
	if (data != nullptr)
		delete []data;

}

bool Image::isCompressed() const
{
    switch (format) {
        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
        case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
            return true;
        default:
            return false;
    }
}

int Image::getComponents(int fmt) const
{
    switch (fmt) {
        // Uncompressed images
        case GL_RGBA:
        case GL_BGRA_EXT:
            return 4;
        case GL_RGB:
        case GL_BGR_EXT:
            return 3;
        case GL_LUMINANCE_ALPHA:
            return 2;
        case GL_ALPHA:
        case GL_LUMINANCE:
            return 1;

        // Compressed images
        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
            return 3;
        case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
            return 4;

        // Unknown format
        default:
            return 0;
    }
}

int Image::getMipLevelSize(int w, int h, int mip, int fmt) const
{
    w = std::max(w >> mip, 1);
    h = std::max(h >> mip, 1);

    switch (fmt) {
        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
            return ((w + 3) /4 ) * ((h + 3) / 4) * 8;

        case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
            return ((w + 3) /4 ) * ((h + 3) / 4) * 16;

        default:
            return h * pad(w * getComponents(fmt));
    }
}

int Image::getMipLevelSize(int mip) const
{
    if (mip >= mipLevels)
        return 0;
    return getMipLevelSize(width, height, mip, format);
}

uint8_t *Image::getMipLevel(int mip)
{
    if (mip >= mipLevels)
        return nullptr;
    int ofs = 0;
    for (int lod = 0; lod < mip; lod++)
        ofs += getMipLevelSize(mip);
    return data + ofs;
}

Image *loadImage(std::string &fname)
{
	Image *img = nullptr;

//	img = osdLoadImage(fname);

	return img;
}

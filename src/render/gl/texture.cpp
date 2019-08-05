/*
 * texture.cpp
 *
 *  Created on: Aug 5, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/texture.h"

glTexture::glTexture(int w, int h, int lod)
: Texture(w, h, lod)
{
}

glTexture::~glTexture()
{
	if (glName != 0)
		glDeleteTextures(1, (GLuint *)&glName);
}

int glTexture::getFormat() const
{
	return format;
}

bool glTexture::setFormat(int fmt)
{
	components = getComponents(fmt);
	if (components == 0)
		return false;
	format = fmt;

	if (data != nullptr)
		delete [] data;

	// Initialize image data for new format
	size = 0;
	for (int lod = 0; lod < mipLevels; lod++)
		size += getMipDataSize(lod);

	// Create image space
	data = new uint8_t[size];

	return true;
}

bool glTexture::isCompressed() const
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

int glTexture::getComponents(int fmt) const
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

int glTexture::getMipSize(int fmt, int w, int h, int mip) const
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

void glTexture::load(int target)
{
    glGenTextures(1, (GLuint *)&glName);
    glBindTexture(GL_TEXTURE_2D, glName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glCompressedTexImage2DARB((GLenum)target, 0, format,
        width, height, 0, getMipDataSize(0), getMipData(0));
}

void glTexture::bind()
{
	if (initFlag == false) {
		load(GL_TEXTURE_2D);
		initFlag = true;
	}
	glBindTexture(GL_TEXTURE_2D, glName);
}

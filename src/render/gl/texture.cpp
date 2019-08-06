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

int glTexture::getBorderAddress() const
{
	switch (borderMode) {
	case Wrap:
		return GL_REPEAT;
	case EdgeClamp:
		return GL_CLAMP_TO_EDGE;
	case BorderClamp:
		return GL_CLAMP;
	}
	return 0;
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
            return h * pad(w * components);
    }
}

int glTexture::getMipDataSize2(int lod) const
{
    int w = std::max(width >> lod, 1);
    int h = std::max(height >> lod, 1);

    switch (format) {
        case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
            return ((w + 3) /4 ) * ((h + 3) / 4) * 8;

        case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
        case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
            return ((w + 3) /4 ) * ((h + 3) / 4) * 16;

        default:
            return h * pad(w * components);
    }
}

void glTexture::loadMipData(int target)
{

	for (int lod = 0; lod < mipLevels; lod++) {
		int w = std::max(width >> lod, 1);
		int h = std::max(height >> lod, 1);

		glTexImage2D(target, lod, 0, w, h, 0, format,
			GL_UNSIGNED_BYTE, getMipData(lod));
	}
}

void glTexture::load(int target)
{
	bool mipFlag = mipMode != NoMipMaps;
	int  borderFlag = getBorderAddress();

    glGenTextures(1, (GLuint *)&glName);
    glBindTexture(GL_TEXTURE_2D, glName);

    glTexParameteri(target, GL_TEXTURE_WRAP_S, borderFlag);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, borderFlag);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER,
    	mipFlag ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);

    if (mipFlag == true)
    	loadMipData(target);
    else
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

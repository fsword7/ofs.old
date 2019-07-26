/*
 * texture.cpp
 *
 *  Created on: Jul 26, 2019
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "render/gl/texture.h"

glImageTexture::~glImageTexture()
{
	if (glName != 0)
		glDeleteTextures(1, (GLuint *)&glName);
}

void glImageTexture::load(Image *img, int target)
{
    glGenTextures(1, (GLuint *)&glName);
    glBindTexture(GL_TEXTURE_2D, glName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glCompressedTexImage2DARB((GLenum)target, 0, img->getFormat(),
        img->getWidth(), img->getHeight(),
        0, img->getMipLevelSize(0), img->getMipLevel(0));
}

void glImageTexture::bind()
{
	if (initFlag == false) {
		load(image, GL_TEXTURE_2D);
		initFlag = true;
	}
	glBindTexture(GL_TEXTURE_2D, glName);
}

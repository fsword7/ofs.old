/*
 * context.cpp
 *
 *  Created on: Aug 11, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "util/color.h"
#include "render/gl/context.h"

glContext::~glContext()
{
	if (vao != 0)
		glDeleteVertexArrays(1, &vao);
	if (vbo != 0)
		glDeleteBuffers(1, &vbo);
	if (ebo != 0)
		glDeleteBuffers(1, &ebo);
}

void glContext::init()
{
	// Initialize virtual buffers
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

}

void glContext::start()
{
}

void glContext::finish()
{
}

void glContext::assign(bType type, void *data, uint32_t size) const
{
	switch (type) {
	case glVBO:
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		break;
	case glEBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		break;
	}
}

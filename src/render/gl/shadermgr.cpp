/*
 * shadermgr.cpp - Shader Manager facility
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "render/gl/shadermgr.h"

static const char *glslVersion = "#version 120\n";

static const char *defaultVertrexShaderSource =
	"void main(void) {\n"
	"   gl_Position = ftransform();\n"
	"}\n";

static const char *defaultFragmentShaderSource =
	"void main(void) {\n"
	"   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\n";


glShaderManager::glShaderManager()
{
}

glShaderManager::~glShaderManager()
{
}

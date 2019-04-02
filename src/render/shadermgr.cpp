/*
 * shadermgr.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
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


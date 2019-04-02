/*
 * shadermgr.cpp - Shader Manager facility
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "render/gl/shadermgr.h"

using namespace std;

static const char *glslVersionHeader = "#version 120\n";

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

string addPointSize()
{
	string source;

	source += "\tfloat ptSize = pointScale * pointSize / length(vec3(gl_ModelViewProject * gl_Vertex));\n";
	source += "\tgl_PointSize = ptSize;\n";
//	source += "\tpointFade = min(1.0, ptSize * ptSize);\n";
	return source;
}

Shader *glShaderManager::buildVertexShader(const ShaderProperties &shp)
{
	string source(glslVersionHeader);

	// Begin main() function
	source += "\nvoid main(void)\n{\n";

	if (shp.type == ShaderProperties::shrPointSprite)
		source += addPointSize();

	source += "\tgl_Position = ftransform();\n";
	source += "}\n";

	return nullptr;
}

Shader *glShaderManager::buildFragmentShader(const ShaderProperties &shp)
{
	string source(glslVersionHeader);

	// Begin main() function
	source += "\nvoid main(void)\n{\n";
	source += "\tvec4 color;\n";

	source += "\tcolor = vec4(1.0, 1.0, 1.0, 1.0);\n";
	source += "}\n";

	return nullptr;
}

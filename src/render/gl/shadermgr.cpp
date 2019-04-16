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

	source += "   float ptSize = pointScale * pointSize / length(vec3(gl_ModelViewProject * gl_Vertex));\n";
	source += "   gl_PointSize = ptSize;\n";
//	source += "   pointFade = min(1.0, ptSize * ptSize);\n";
	return source;
}

const string glShaderManager::getVariableType(ShaderVariableType type)
{
	switch(type) {
	case shrFloat:
		return "float";
	case shrDouble:
		return "double";
	case shrVector2:
		return "vec2";
	case shrVector3:
		return "vec3";
	case shrVector4:
		return "vec4";
	case shrSampler1D:
		return "sample1D";
	case shrSampler2D:
		return "sampler2D";
	case shrSampler3D:
		return "sampler3D";
	case shrSamplerCube:
		return "samplerCube";
	default:
		return "unknown";
	}
}

Shader *glShaderManager::buildVertexShader(const ShaderProperties &shp)
{
	string source(glslVersionHeader);

	// Begin main() function
	source += "\nvoid main(void)\n{\n";

	if (shp.type == ShaderProperties::shrPointSprite)
		source += addPointSize();

	source += "   gl_Position = ftransform();\n";
	source += "}\n";

	return nullptr;
}

Shader *glShaderManager::buildFragmentShader(const ShaderProperties &shp)
{
	string source(glslVersionHeader);

	// Begin main() function
	source += "\nvoid main(void)\n{\n";
	source += "   vec4 color;\n";

	source += "   color = vec4(1.0, 1.0, 1.0, 1.0);\n";
	source += "}\n";

	return nullptr;
}

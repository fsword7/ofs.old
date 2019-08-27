/*
 * shadermgr.cpp - Shader Manager facility
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/shader.h"
#include "render/gl/shadermgr.h"

using namespace std;

static const char *glslVersionHeader = "#version 120\n\n";

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

string glShaderManager::declareUniform(const string &name, ShaderVariableType type)
{
	return string("uniform ") + getVariableType(type) + " " + name + ";\n";
}

string glShaderManager::declareVarying(const string &name, ShaderVariableType type)
{
	return string("varying ") + getVariableType(type) + " " + name + ";\n";
}

string glShaderManager::declareAttribute(const string &name, ShaderVariableType type)
{
	return string("attribute ") + getVariableType(type) + " " + name + ";\n";
}

Shader *glShaderManager::buildStarVertexShader(const ShaderProperties &shp)
{
	string source(glslVersionHeader);

	if (shp.type == ShaderProperties::shrPointStar)
	{
//		source += declareUniform("pointScale", shrFloat);
		source += declareAttribute("pointSize", shrFloat);
	}
	source += declareVarying("color", shrVector4);

	// Begin main() function
	source += "\nvoid main(void)\n{\n";

	source += "   color = gl_Color;\n";
	if (shp.type & ShaderProperties::shrPointStar)
		source += "   gl_PointSize = pointSize;\n";

	source += "   gl_Position = ftransform();\n";
	source += "}\n";

	dumpVertexSource(cout, source);

	glShader *vs;
	vector<string> vsrc;
	vsrc.push_back(source);
	ShaderStatus st = glShader::create(cout, shrVertexProcessor, vsrc, &vs);

	return st == shrSuccessful ? vs : nullptr;
}

Shader *glShaderManager::buildStarFragmentShader(const ShaderProperties &shp)
{
	string source(glslVersionHeader);

	source += declareUniform("starTex", shrSampler2D);
	source += declareVarying("color", shrVector4);

	// Begin main() function
	source += "\nvoid main(void)\n{\n";
	source += "   gl_FragColor = texture2D(starTex, gl_PointCoord) * color;\n";
	source += "}\n";

	dumpFragmentSource(cout, source);

	glShader *fs;
	vector<string> vsrc;
	vsrc.push_back(source);
	ShaderStatus st = glShader::create(cout, shrFragmentProcessor, vsrc, &fs);

	return st == shrSuccessful ? fs : nullptr;
}

Shader *glShaderManager::buildVertexShader(const ShaderProperties &shp)
{
	string source(glslVersionHeader);

//	if (shp.type & ShaderProperties::shrPointSprite) {
//		source += declareUniform("pointScale", shrFloat);
//		source += declareAttribute("pointSize", shrFloat);
//		source += declareVarying("pointFade", shrFloat);
//	}

	// Begin main() function
	source += "\nvoid main(void)\n{\n";

//	if (shp.type == ShaderProperties::shrPointSprite)
//		source += addPointSize();

	source += "   gl_Position = ftransform();\n";
	source += "}\n";

	dumpVertexSource(cout, source);

	glShader *vs;
	vector<string> vsrc;
	vsrc.push_back(source);
	ShaderStatus st = glShader::create(cout, shrVertexProcessor, vsrc, &vs);

	return st == shrSuccessful ? vs : nullptr;
}

Shader *glShaderManager::buildFragmentShader(const ShaderProperties &shp)
{
	string source(glslVersionHeader);

	// Begin main() function
	source += "\nvoid main(void)\n{\n";
	source += "   vec4 color;\n";

	source += "   color = vec4(1.0, 1.0, 1.0, 1.0);\n";
	source += "}\n";

	dumpFragmentSource(cout, source);

	glShader *fs;
	vector<string> vsrc;
	vsrc.push_back(source);
	ShaderStatus st = glShader::create(cout, shrFragmentProcessor, vsrc, &fs);

	return st == shrSuccessful ? fs : nullptr;
}

ShaderStatus glShaderManager::createProgram(ostream &out, const ShaderProperties &shp,
		Shader &fs, Shader &vs, ShaderProgram **pgm)
{
	glShaderProgram *npgm = new glShaderProgram();

	npgm->attach(dynamic_cast<glShader&>(vs));
	npgm->attach(dynamic_cast<glShader&>(fs));

	if (shp.type & ShaderProperties::shrPointStar)
		glBindAttribLocation(npgm->getID(), 7, "pointSize");

	ShaderStatus st = npgm->link(out);

	if (st == shrSuccessful)
		*pgm = npgm;
	return st;
}

ShaderStatus glShaderManager::createProgram(ostream &out, const std::string &vsSource,
		const std::string &fsSource, ShaderProgram **pgm)
{
	std::vector<std::string> vsSourcev;
	std::vector<std::string> fsSourcev;

	vsSourcev.push_back(vsSource);
	fsSourcev.push_back(fsSource);

	glShader *vs, *fs;
	ShaderStatus st;

	st = glShader::create(out, shrVertexProcessor, vsSourcev, &vs);
	st = glShader::create(out, shrFragmentProcessor, fsSourcev, &fs);

	glShaderProgram *npgm = new glShaderProgram();

	npgm->attach(*vs);
	npgm->attach(*fs);

	glBindAttribLocation(npgm->getID(), 7, "pointSize");

	st = npgm->link(out);
	if (st == shrSuccessful)
		*pgm = npgm;

	return shrSuccessful;
}

ShaderPackage *glShaderManager::createPackage(ShaderProgram &pgm, const ShaderProperties &shp)
{
	return new glShaderPackage(pgm, shp);
}

ShaderPackage *glShaderManager::createPackage(ShaderProgram &pgm)
{
	return new glShaderPackage(pgm);
}

// ***************************************************************

glShaderIntegerParameter glShaderPackage::setIntegerParam(const std::string &name)
{
	return glShaderIntegerParameter(program.getID(), name.c_str());
}

glShaderIntegerParameter glShaderPackage::setSamplerParam(const std::string &name)
{
	return glShaderIntegerParameter(program.getID(), name.c_str());

}

void glShaderPackage::initParams()
{
	mvp = glShaderMat4FParameter(program.getID(), "mvp");
}

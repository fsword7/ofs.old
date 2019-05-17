/*
 * shadermgr.h
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

#include "render/shadermgr.h"

class glShaderManager : public ShaderManager
{
public:
	glShaderManager();
	~glShaderManager();

protected:
	const std::string getVariableType(ShaderVariableType type) override;

	std::string declareUniform(const std::string &name, ShaderVariableType type);
	std::string declareVarying(const std::string &name, ShaderVariableType type);
	std::string declareAttribute(const std::string &name, ShaderVariableType type);

	ShaderStatus createProgram(ostream &out, const ShaderProperties &shp,
			Shader &fs, Shader &vs, ShaderProgram **pgm) override;
	ShaderPackage *createPackage(ShaderProgram &pgm, const ShaderProperties &shp) override;

	Shader *buildStarVertexShader(const ShaderProperties &shp) override;
	Shader *buildStarFragmentShader(const ShaderProperties &shp) override;

	Shader *buildVertexShader(const ShaderProperties &shp) override;
	Shader *buildFragmentShader(const ShaderProperties &shp) override;
};

class glShaderPackage : public ShaderPackage
{
public:
	enum {
		PointSizeAttributeIndex = 7
	};

	glShaderPackage(ShaderProgram &pgm, const ShaderProperties &shp)
	: ShaderPackage(pgm, shp) {};
	~glShaderPackage() = default;

	glShaderFloatParameter pointSize;
	glShaderFloatParameter pointScale;
	glShaderVec4FParameter color;

};

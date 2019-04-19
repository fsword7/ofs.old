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

	Shader *buildStarVertexShader(const ShaderProperties &shp) override;
	Shader *buildStarFragmentShader(const ShaderProperties &shp) override;

	Shader *buildVertexShader(const ShaderProperties &shp) override;
	Shader *buildFragmentShader(const ShaderProperties &shp) override;
};

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

	Shader *buildVertexShader(const ShaderProperties &shp) override;
	Shader *buildFragmentShader(const ShaderProperties &shp) override;

protected:
	const std::string getVariableType(ShaderVariableType type) override;

};

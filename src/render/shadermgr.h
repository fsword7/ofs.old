/*
 * shadermgr.h - Shader Program Manager
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#pragma once

class Shader;

class ShaderProperties
{
public:
	ShaderProperties() : type(shrNone) {}
	~ShaderProperties() = default;

	enum ShaderType {
		shrNone				= 0x0000,
		shrPointSprite		= 0x0001, // Displaying stars as point in background
		shrNormalTexture	= 0x0002
	};

public:
	ShaderType type;
};

class ShaderManager
{
public:
	ShaderManager() {}
	virtual ~ShaderManager() = default;

	virtual Shader *buildVertexShader(const ShaderProperties &shp) = 0;
	virtual Shader *buildFragmentShader(const ShaderProperties &shp) = 0;

protected:
//	std::map<ShaderProperties, Program *> shaders;
};

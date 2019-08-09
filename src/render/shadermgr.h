/*
 * shadermgr.h - Shader Program Manager
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#pragma once

class Shader;
class ShaderProgram;

enum ShaderVariableType
{
	shrFloat,
	shrDouble,
	shrVector2,
	shrVector3,
	shrVector4,
	shrSampler1D,
	shrSampler2D,
	shrSampler3D,
	shrSamplerCube
};

class ShaderProperties
{
public:
	ShaderProperties() : type(shrNone) {}
	~ShaderProperties() = default;

	enum ShaderType {
		shrNone				= 0x0000,
		shrPointStar		= 0x0001, // Displaying stars as point in background
		shrNormalTexture	= 0x0002
	};

public:
	ShaderType type;
	bool starShader = false;
};

class ShaderPackage
{
public:
	ShaderPackage(ShaderProgram &pgm);
	ShaderPackage(ShaderProgram &pgm, const ShaderProperties &shp);
	virtual ~ShaderPackage() = default;

	void use() { program.use(); };

protected:
	ShaderProgram &program;
	const ShaderProperties properties;
};

class ShaderManager
{
public:
	ShaderManager() {}
	virtual ~ShaderManager() = default;

	ShaderPackage *createShader(const ShaderProperties &shp);
	ShaderPackage *createShader(const std::string &name);
	ShaderPackage *createShader(const std::string &name, const std::string &vs, const std::string &fs);
	ShaderPackage *buildPrograms(const ShaderProperties &shp);
	ShaderPackage *buildPrograms(const std::string &vs, const std::string &fs);

protected:
	virtual const std::string getVariableType(ShaderVariableType type) = 0;

	virtual ShaderStatus createProgram(ostream &out, const ShaderProperties &shp,
			Shader &fs, Shader &vs, ShaderProgram **pgm) = 0;
	virtual ShaderStatus createProgram(ostream &out,
		const std::string &vs, const std::string &fs,
		ShaderProgram **pgm) = 0;

	virtual ShaderPackage *createPackage(ShaderProgram &pgm) = 0;
	virtual ShaderPackage *createPackage(ShaderProgram &pgm, const ShaderProperties &shp) = 0;

	virtual Shader *buildStarVertexShader(const ShaderProperties &shp) = 0;
	virtual Shader *buildStarFragmentShader(const ShaderProperties &shp) = 0;

	virtual Shader *buildVertexShader(const ShaderProperties &shp) = 0;
	virtual Shader *buildFragmentShader(const ShaderProperties &shp) = 0;

	void dumpSource(ostream &out, const std::string &source);
	void dumpVertexSource(ostream &out, const std::string &source);
	void dumpFragmentSource(ostream &out, const std::string &source);

protected:
//	std::map<ShaderProperties, Program *> shaders;
};

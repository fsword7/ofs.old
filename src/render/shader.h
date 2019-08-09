/*
 * shader.h
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#pragma once

enum ShaderType {
	shrUnknown = 0,
	shrVertexProcessor,
	shrFragmentProcessor
};

enum ShaderStatus {
	shrSuccessful,
	shrCompileError,
	shrLinkError,
	shrOutOfMemory,
	shrEmptyProgram
};


class ShaderProgram
{
public:
	ShaderProgram();
	virtual ~ShaderProgram();

	// Virtual function calls
	virtual int  getID() const = 0;
	virtual void use() = 0;
};


class Shader
{
public:

	Shader(ShaderType type);
	virtual ~Shader();

	inline ShaderType getType() const { return type; }

	virtual ShaderStatus compile(const vector<string>& source) = 0;

private:
	ShaderType type;
};


class ShaderIntegerParameter
{
public:
	ShaderIntegerParameter() = default;
	virtual ~ShaderIntegerParameter() = default;

	virtual ShaderIntegerParameter &operator = (int v) = 0;
};

class ShaderFloatParameter
{
public:
	ShaderFloatParameter() = default;
	virtual ~ShaderFloatParameter() = default;

	virtual ShaderFloatParameter &operator = (float v) = 0;
};

class ShaderVec3FParameter
{
public:
	ShaderVec3FParameter() = default;
	virtual ~ShaderVec3FParameter() = default;

	virtual ShaderVec3FParameter &operator = (const vec3f_t &v) = 0;
};

class ShaderVec4FParameter
{
public:
	ShaderVec4FParameter() = default;
	virtual ~ShaderVec4FParameter() = default;

	virtual ShaderVec4FParameter &operator = (const vec4f_t &v) = 0;
};

class ShaderMat3FParameter
{
public:
	ShaderMat3FParameter() = default;
	virtual ~ShaderMat3FParameter() = default;

	virtual ShaderMat3FParameter &operator = (const mat3f_t &v) = 0;
};

class ShaderMat4FParameter
{
public:
	ShaderMat4FParameter() = default;
	virtual ~ShaderMat4FParameter() = default;

	virtual ShaderMat4FParameter &operator = (const mat4f_t &v) = 0;
};


class ShaderDoubleParameter
{
public:
	ShaderDoubleParameter() = default;
	virtual ~ShaderDoubleParameter() = default;

	virtual ShaderDoubleParameter &operator = (double v) = 0;
};

class ShaderVec3DParameter
{
public:
	ShaderVec3DParameter() = default;
	virtual ~ShaderVec3DParameter() = default;

	virtual ShaderVec3DParameter &operator = (const vec3d_t &v) = 0;
};

class ShaderVec4DParameter
{
public:
	ShaderVec4DParameter() = default;
	virtual ~ShaderVec4DParameter() = default;

	virtual ShaderVec4DParameter &operator = (const vec4d_t &v) = 0;
};

class ShaderMat3DParameter
{
public:
	ShaderMat3DParameter() = default;
	virtual ~ShaderMat3DParameter() = default;

	virtual ShaderMat3DParameter &operator = (const mat3d_t &v) = 0;
};

class ShaderMat4DParameter
{
public:
	ShaderMat4DParameter() = default;
	virtual ~ShaderMat4DParameter() = default;

	virtual ShaderMat4DParameter &operator = (const mat4d_t &v) = 0;
};

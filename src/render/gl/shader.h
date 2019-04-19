/*
 * shader.h
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#pragma once

#include <GL/glew.h>
#include "render/shader.h"

class glShader : public Shader
{
public:
	glShader(ShaderType type);
	~glShader();

	inline GLuint getID() const { return id; }

	ShaderStatus compile(const vector<string>& source);

	const string getLogInfo();

	static ShaderStatus create(ostream &out, ShaderType type,
		const vector<string>& source, glShader **shader);

private:
	GLuint id;
};

class glShaderProgram : public ShaderProgram
{
public:
	glShaderProgram();
	~glShaderProgram();

	inline GLuint getID() const { return id; }

	void attach(const glShader &shader);
	ShaderStatus link(ostream &out);

	const string getLogInfo();

	// Virtual function calls
	void use() override;

private:
	GLuint id;
};


class glShaderFloatParameter
{
public:
	glShaderFloatParameter() = default;
	glShaderFloatParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	glShaderFloatParameter &operator = (float v);

private:
	int slot = -1;
};

class glShaderVec3FParameter
{
public:
	glShaderVec3FParameter() = default;
	glShaderVec3FParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	glShaderVec3FParameter &operator = (const vec3f_t &v);

private:
	int slot = -1;
};

class glShaderVec4FParameter
{
public:
	glShaderVec4FParameter() = default;
	glShaderVec4FParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	glShaderVec4FParameter &operator = (const vec4f_t &v);

private:
	int slot = -1;
};

class glShaderDoubleParameter
{
public:
	glShaderDoubleParameter() = default;
	glShaderDoubleParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	glShaderDoubleParameter &operator = (double v);

private:
	int slot = -1;
};

class glShaderVec3DParameter
{
public:
	glShaderVec3DParameter() = default;
	glShaderVec3DParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	glShaderVec3DParameter &operator = (const vec3d_t &v);

private:
	int slot = -1;
};

class glShaderVec4DParameter
{
public:
	glShaderVec4DParameter() = default;
	glShaderVec4DParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	glShaderVec4DParameter &operator = (const vec4d_t &v);

private:
	int slot = -1;
};

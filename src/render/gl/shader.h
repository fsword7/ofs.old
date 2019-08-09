/*
 * shader.h
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#pragma once

#include <GL/glew.h>
#include "render/shader.h"

class glShader;

class glShaderProgram : public ShaderProgram
{
public:
	glShaderProgram();
	~glShaderProgram();

	int getID() const { return id; }

	void attach(const glShader &shader);
	ShaderStatus link(ostream &out);

	const string getLogInfo();

	// Virtual function calls
	void use() override;

private:
	GLuint id;
};


class glShader : public Shader
{
public:
	glShader(ShaderType type);
	~glShader();

	GLuint getID() const { return id; }

	ShaderStatus compile(const vector<string>& source);

	const string getLogInfo();

	static ShaderStatus create(ostream &out, ShaderType type,
		const vector<string>& source, glShader **shader);

private:
	GLuint id;
};


class glShaderIntegerParameter : public ShaderIntegerParameter
{
public:
	glShaderIntegerParameter() = default;
	glShaderIntegerParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderIntegerParameter &operator = (int v);

private:
	int slot = -1;
};

class glShaderFloatParameter : public ShaderFloatParameter
{
public:
	glShaderFloatParameter() = default;
	glShaderFloatParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderFloatParameter &operator = (float v);

private:
	int slot = -1;
};

class glShaderVec3FParameter : public ShaderVec3FParameter
{
public:
	glShaderVec3FParameter() = default;
	glShaderVec3FParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderVec3FParameter &operator = (const vec3f_t &v);

private:
	int slot = -1;
};

class glShaderVec4FParameter : public ShaderVec4FParameter
{
public:
	glShaderVec4FParameter() = default;
	glShaderVec4FParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderVec4FParameter &operator = (const vec4f_t &v);

private:
	int slot = -1;
};

class glShaderMat3FParameter : public ShaderMat3FParameter
{
public:
	glShaderMat3FParameter() = default;
	glShaderMat3FParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderMat3FParameter &operator = (const mat3f_t &v);

private:
	int slot = -1;
};

class glShaderMat4FParameter : public ShaderMat4FParameter
{
public:
	glShaderMat4FParameter() = default;
	glShaderMat4FParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderMat4FParameter &operator = (const mat4f_t &v);

private:
	int slot = -1;
};

class glShaderDoubleParameter : public ShaderDoubleParameter
{
public:
	glShaderDoubleParameter() = default;
	glShaderDoubleParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderDoubleParameter &operator = (double v);

private:
	int slot = -1;
};

class glShaderVec3DParameter : public ShaderVec3DParameter
{
public:
	glShaderVec3DParameter() = default;
	glShaderVec3DParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderVec3DParameter &operator = (const vec3d_t &v);

private:
	int slot = -1;
};

class glShaderVec4DParameter : public ShaderVec4DParameter
{
public:
	glShaderVec4DParameter() = default;
	glShaderVec4DParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderVec4DParameter &operator = (const vec4d_t &v);

private:
	int slot = -1;
};

class glShaderMat3DParameter : public ShaderMat3DParameter
{
public:
	glShaderMat3DParameter() = default;
	glShaderMat3DParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderMat3DParameter &operator = (const mat3d_t &v);

private:
	int slot = -1;
};

class glShaderMat4DParameter : public ShaderMat4DParameter
{
public:
	glShaderMat4DParameter() = default;
	glShaderMat4DParameter(GLuint obj, const char *name)
	{
		slot = glGetUniformLocation(obj, name);
	}

	ShaderMat4DParameter &operator = (const mat4d_t &v);

private:
	int slot = -1;
};

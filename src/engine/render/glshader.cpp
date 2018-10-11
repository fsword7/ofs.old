/*
 * shader.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "engine/render/render.h"
#include "engine/render/shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

// ******************************

glShader::glShader(GLuint _id)
: id(_id)
{
}

glShader::~glShader()
{
}

ShaderStatus glShader::compile(const vector<string>& source)
{
	GLint status;

	if (source.empty())
		return ShaderStatus::EmptyProgram;

	const char **src = new const char*[source.size()];
	for (unsigned int idx = 0; idx < source.size(); idx++)
		src[idx] = source[idx].c_str();

	glShaderSource(id, source.size(), src, nullptr);
	delete [] src;

	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
		return ShaderStatus::CompileError;
	return ShaderStatus::Successful;
}

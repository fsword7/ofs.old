/*
 * shader.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/gl/scene.h"
#include "render/gl/shader.h"

glShader::glShader(ShaderType type)
: Shader(type)
{
	GLenum idType;

	switch (type) {
	case shrVertexProcessor:
		idType = GL_VERTEX_SHADER;
		break;
	case shrFragmentProcessor:
		idType = GL_FRAGMENT_SHADER;
		break;
	}

	id = glCreateShader(idType);
}

glShader::~glShader()
{
	glDeleteShader(id);
}

ShaderStatus glShader::create(ostream &out, ShaderType type,
	const vector<string>& source, glShader **shader)
{
	glShader *newShader = new glShader(type);
	ShaderStatus status;
	string log;

	if (newShader == nullptr)
		return ShaderStatus::shrOutOfMemory;

	status = newShader->compile(source);
	if (status != ShaderStatus::shrSuccessful) {
		log = newShader->getLogInfo();
		out << "\nCompiling shader source error:\n" << endl;
		out << log << endl;
		out.flush();

		delete newShader;
		return status;
	}

	*shader = newShader;
	return ShaderStatus::shrSuccessful;
}

ShaderStatus glShader::compile(const vector<string>& source)
{
	GLint status;

	if (source.empty())
		return ShaderStatus::shrEmptyProgram;

	const char **src = new const char*[source.size()];
	for (unsigned int idx = 0; idx < source.size(); idx++)
		src[idx] = source[idx].c_str();

	glShaderSource(id, source.size(), src, nullptr);
	delete [] src;

	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
		return ShaderStatus::shrCompileError;
	return ShaderStatus::shrSuccessful;
}

const string glShader::getLogInfo()
{
	GLint   lsize = 0;
	GLsizei size  = 0;

	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lsize);
	if (lsize <= 0)
		return string();

	char *clog = new char[lsize];
	if (clog == nullptr)
		return string();

	glGetShaderInfoLog(id, lsize, &size, clog);
	string slog(clog, size);
	delete [] clog;

	return slog;
}

// ***********************************

glShaderProgram::glShaderProgram()
{
	id = glCreateProgram();
}

glShaderProgram::~glShaderProgram()
{
	glDeleteProgram(id);
}

void glShaderProgram::attach(const glShader &shader)
{
	glAttachShader(id, shader.getID());
}

ShaderStatus glShaderProgram::link(ostream &out)
{
	GLint  status;
	string log;

	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		log = getLogInfo();
		out << "\nLinking shader program error:\n" << endl;
		out << log << endl;

		return ShaderStatus::shrLinkError;
	}

	return ShaderStatus::shrSuccessful;
}

const string glShaderProgram::getLogInfo()
{
	GLint   lsize = 0;
	GLsizei size  = 0;

	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &lsize);
	if (lsize <= 0)
		return string();

	char *clog = new char[lsize];
	if (clog == nullptr)
		return string();

	glGetProgramInfoLog(id, lsize, &size, clog);
	string slog(clog, size);
	delete [] clog;

	return slog;
}

void glShaderProgram::use()
{
	glUseProgram(id);
}

ShaderIntegerParameter &glShaderIntegerParameter::operator = (int v)
{
	if (slot != -1)
		glUniform1i(slot, v);
	return *this;
}

ShaderFloatParameter &glShaderFloatParameter::operator = (float v)
{
	if (slot != -1)
		glUniform1f(slot, v);
	return *this;
}

ShaderVec3FParameter &glShaderVec3FParameter::operator = (const vec3f_t &v)
{
	if (slot != -1)
		glUniform3f(slot, v.x, v.y, v.z);
	return *this;
}

ShaderVec4FParameter &glShaderVec4FParameter::operator = (const vec4f_t &v)
{
	if (slot != -1)
		glUniform4f(slot, v.x, v.y, v.z, v.w);
	return *this;
}

ShaderMat3FParameter &glShaderMat3FParameter::operator = (const mat3f_t &m)
{
	if (slot != -1)
		glUniformMatrix3fv(slot, 1, GL_FALSE, glm::value_ptr(m));
	return *this;
}

ShaderMat4FParameter &glShaderMat4FParameter::operator = (const mat4f_t &m)
{
	if (slot != -1)
		glUniformMatrix4fv(slot, 1, GL_FALSE, glm::value_ptr(m));
	return *this;
}

ShaderDoubleParameter &glShaderDoubleParameter::operator = (double v)
{
	if (slot != -1)
		glUniform1d(slot, v);
	return *this;
}

ShaderVec3DParameter &glShaderVec3DParameter::operator = (const vec3d_t &v)
{
	if (slot != -1)
		glUniform3d(slot, v.x, v.y, v.z);
	return *this;
}

ShaderVec4DParameter &glShaderVec4DParameter::operator = (const vec4d_t &v)
{
	if (slot != -1)
		glUniform4d(slot, v.x, v.y, v.z, v.w);
	return *this;
}

ShaderMat3DParameter &glShaderMat3DParameter::operator = (const mat3d_t &m)
{
	if (slot != -1)
		glUniformMatrix3dv(slot, 1, GL_FALSE, glm::value_ptr(m));
	return *this;
}

ShaderMat4DParameter &glShaderMat4DParameter::operator = (const mat4d_t &m)
{
	if (slot != -1)
		glUniformMatrix4dv(slot, 1, GL_FALSE, glm::value_ptr(m));
	return *this;
}

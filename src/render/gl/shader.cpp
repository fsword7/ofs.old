/*
 * shader.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "render/gl/scene.h"
#include "render/gl/shader.h"

Shader::Shader(ShaderType _type)
: type(_type)
{
}

Shader::~Shader()
{
}

// ******************************

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

ShaderStatus glShader::create(ShaderType type,
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
		cerr << "\nCompiling shader program error:\n" << endl;
		cerr << log << endl;

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

Program::Program()
{
}

Program::~Program()
{
}

// ***********************************

glProgram::glProgram(GLuint _id)
: id(_id)
{
	id = glCreateProgram();
}

glProgram::~glProgram()
{
	glDeleteProgram(id);
}

void glProgram::attach(const glShader &shader)
{
	glAttachShader(id, shader.getID());
}

ShaderStatus glProgram::link()
{
	GLint  status;
	string log;

	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		log = getLogInfo();
		cerr << "\nLinking shader program error:\n" << endl;
		cerr << log << endl;

		return ShaderStatus::shrLinkError;
	}

	return ShaderStatus::shrSuccessful;
}

const string glProgram::getLogInfo()
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

void glProgram::use()
{
	glUseProgram(id);
}

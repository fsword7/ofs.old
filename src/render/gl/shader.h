/*
 * shader.h
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#pragma once

#include "render/shader.h"

class glShader : public Shader
{
public:
	glShader(ShaderType type);
	~glShader();

	inline GLuint getID() const { return id; }

	ShaderStatus compile(const vector<string>& source);

	const string getLogInfo();

	static ShaderStatus create(ShaderType type,
		const vector<string>& source, glShader **shader);

private:
	GLuint id;
};

class glProgram : public Program
{
public:
	glProgram(GLuint id);
	~glProgram();

	inline GLuint getID() const { return id; }

	void attach(const glShader &shader);
	ShaderStatus link();

	const string getLogInfo();

	void use();

private:
	GLuint id;
};

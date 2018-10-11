/*
 * shader.h
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#pragma once

enum ShaderStatus {
	Successful,
	CompileError,
	LinkError,
	OutOfMemory,
	EmptyProgram
};

class Shader
{
public:

	Shader();
	virtual ~Shader();

	virtual ShaderStatus compile(const vector<string>& source) = 0;

};

class glShader : public Shader
{
public:
	glShader(GLuint id);
	~glShader();

	inline GLuint getID() const { return id; }

	ShaderStatus compile(const vector<string>& source);

private:
	GLuint id;
};

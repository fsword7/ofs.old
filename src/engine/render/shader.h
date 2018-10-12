/*
 * shader.h
 *
 *  Created on: Oct 11, 2018
 *      Author: Tim Stark
 */

#pragma once

enum ShaderType {
	Unknown = 0,
	VertexProcessor,
	FragmentProcessor
};

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

	Shader(ShaderType type);
	virtual ~Shader();

	inline ShaderType getType() const { return type; }

	virtual ShaderStatus compile(const vector<string>& source) = 0;

private:
	ShaderType type;
};

class Program
{
public:
	Program();
	~Program();
};


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

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



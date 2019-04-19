/*
 * shadermgr.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/shader.h"
#include "render/shadermgr.h"

void ShaderManager::dumpSource(ostream &out, const std::string &source)
{
	bool newLine = true;
	int lineNumber = 0;

	for (int idx = 0; idx < source.length(); idx++) {
		if (newLine == true) {
			lineNumber++;
			out << setw(4) << lineNumber << ": ";
			newLine = false;
		}

		out << source[idx];
		if (source[idx] == '\n')
			newLine = true;
	}

	out.flush();
}

void ShaderManager::dumpVertexSource(ostream &out, const std::string &source)
{
	out << "Vertex shader source:" << endl;
	dumpSource(out, source);
	out << endl;
}

void ShaderManager::dumpFragmentSource(ostream &out, const std::string &source)
{
	out << "Fragment shader source:" << endl;
	dumpSource(out, source);
	out << endl;
}

ShaderPackage *ShaderManager::buildPrograms(const ShaderProperties &shp)
{
	Shader *vs = nullptr; // Vertex shader program
	Shader *fs = nullptr; // Fragment shader program

	ShaderProgram *pgm;

	if (shp.starShader == true) {
		vs = buildStarVertexShader(shp);
		fs = buildStarFragmentShader(shp);
	} else {
		vs = buildVertexShader(shp);
		fs = buildFragmentShader(shp);
	}

	if (vs != nullptr && fs != nullptr) {

	} else {

	}

	delete vs;
	delete fs;

	return nullptr;
}

ShaderPackage *ShaderManager::createShader(const ShaderProperties &shp)
{
	ShaderPackage *pkg = buildPrograms(shp);
//	shaders.push_back(pgm);

	return pkg;
}


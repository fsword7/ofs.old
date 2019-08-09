/*
 * shadermgr.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/shader.h"
#include "render/shadermgr.h"

#include <fmt/printf.h>

ShaderPackage::ShaderPackage(ShaderProgram &pgm)
: program(pgm)
{
}

ShaderPackage::ShaderPackage(ShaderProgram &pgm, const ShaderProperties &shp)
: program(pgm), properties(shp)
{
}

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
	ShaderStatus st;

	if (shp.starShader == true) {
		vs = buildStarVertexShader(shp);
		fs = buildStarFragmentShader(shp);
	} else {
		vs = buildVertexShader(shp);
		fs = buildFragmentShader(shp);
	}

	if (vs != nullptr && fs != nullptr) {
		cout << "Linking shader programs..." << endl;
		st = createProgram(cout, shp, *vs, *fs, &pgm);
	}

	delete vs;
	delete fs;

	if (pgm == nullptr)
		return nullptr;
	return createPackage(*pgm, shp);
}

ShaderPackage *ShaderManager::buildPrograms(const std::string &vs, const std::string &fs)
{
//	Shader *vs = nullptr; // Vertex shader program
//	Shader *fs = nullptr; // Fragment shader program

	ShaderProgram *pgm;
	ShaderStatus st;

	dumpVertexSource(cout, vs);
	dumpFragmentSource(cout, fs);

	st = createProgram(cout, vs, fs, &pgm);

	if (st != shrSuccessful || pgm == nullptr)
		return nullptr;
	return createPackage(*pgm);
}

ShaderPackage *ShaderManager::createShader(const ShaderProperties &shp)
{
	ShaderPackage *pkg = buildPrograms(shp);
//	shaders.push_back(pgm);

	return pkg;
}

ShaderPackage *ShaderManager::createShader(const std::string &name)
{
	struct stat st;

	auto vsName = fmt::sprintf("shaders/%s-vert.glsl", name);
	auto fsName = fmt::sprintf("shaders/%s-frag.glsl", name);

	if (stat(vsName.c_str(), &st) == -1){
		fmt::fprintf(cout, "Failed to stat %s: %s\n", vsName, std::strerror(errno));
		return nullptr;
	}
	auto vsSize = st.st_size;

	if (stat(fsName.c_str(), &st) == -1) {
		fmt::fprintf(cout, "Failed to stat %s: %s\n", fsName, std::strerror(errno));
		return nullptr;
	}
	auto fsSize = st.st_size;

	ifstream vsf(vsName);
	if (!vsf.good()) {
		fmt::fprintf(cout, "Failed to open %s: %s\n", vsName, std::strerror(errno));
		return nullptr;
	}

	ifstream fsf(fsName);
	if (!fsf.good()) {
		fmt::fprintf(cout, "Failed to open %s: %s\n", fsName, std::strerror(errno));
		return nullptr;
	}

	std::string vs(vsSize, '\0');
	std::string fs(fsSize, '\0');
	vsf.read(&vs[0], vsSize);
	fsf.read(&fs[0], fsSize);

	ShaderPackage *pkg = buildPrograms(vs, fs);;

	return pkg;
}

ShaderPackage *ShaderManager::createShader(const std::string &name,
		const std::string &vs, const std::string &fs)
{
	ShaderPackage *pkg = buildPrograms(vs, fs);;

	return pkg;
}

/*
 * shadermgr.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/shadermgr.h"


void ShaderManager::createShader(const ShaderProperties &prop)
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

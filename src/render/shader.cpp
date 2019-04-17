/*
 * shader.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/shader.h"

Shader::Shader(ShaderType _type)
: type(_type)
{
}

Shader::~Shader()
{
}

// ******************************

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

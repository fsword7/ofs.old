/*
 * shader.cpp
 *
 *  Created on: Apr 16, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"
#include "render/shader.h"


ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

// ******************************

Shader::Shader(ShaderType _type)
: type(_type)
{
}

Shader::~Shader()
{
}

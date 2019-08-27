#version 400

// vertex buffer data
layout (location = 0) in vec3 vPosition;
//layout (location = 1) in dvec3 vColor;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 mvp;

//out vec4 color;
out vec2 texCoord;

void main(void)
{
	gl_Position = mvp * vec4(vPosition, 1.0);
}

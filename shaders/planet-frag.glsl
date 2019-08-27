#version 400

in vec2 texCoord;
//in vec4 color;

out vec4 fragColor;

uniform sampler2D tex;

void main(void)
{
	fragColor = texture(tex, texCoord);
}

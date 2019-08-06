#version 120
attribute float pointSize;
varying vec4 color;

void main(void)
{
	color = gl_Color;

	gl_PointSize = pointSize;
	gl_Position = ftransform();
}

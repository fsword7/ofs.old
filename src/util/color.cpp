/*
 * color.cpp - HDR color values
 *
 *  Created on: May 17, 2019
 *      Author: Tim Stark
 */

#include "main/core.h"

Color::Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha)
{
	rgba[0] = red;
	rgba[1] = green;
	rgba[2] = blue;
	rgba[3] = alpha;
}

Color::Color(float red, float green, float blue, float alpha)
{
	rgba[0] = red * 65535;
	rgba[1] = green * 65535;
	rgba[2] = blue * 65535;
	rgba[3] = alpha * 65535;
}

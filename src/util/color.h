/*
 * color.h
 *
 *  Created on: May 17, 2019
 *      Author: Tim Stark
 */

#pragma once

class Color
{
public:
	Color();
//	Color(uint16_t red, uint16_t green, uint16_t blue, uint16_t alpha = 0xFFFF);
	Color(float red, float green, float blue, float alpha = 1.0);

	void setAlpha(float a);

	uint16_t rgba[4];
};

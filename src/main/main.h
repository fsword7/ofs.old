/*
 * main.h - Main OFS header
 *
 *  Created on: Oct 2, 2018
 *      Author: Tim Stark
 */

#pragma once

#define APP_FULL_NAME	"Orbital Flight Simulator"
#define APP_SHORT_NAME	"OFS"

// Default window scene size
#define OFS_DEFAULT_WIDTH	1600
#define OFS_DEFAULT_HEIGHT	900
#define OFS_DEFAULT_FOV		50.0

#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <iomanip>

#include <vector>
#include <string>

#include <cstdio>
#include <cerrno>
#include <cstring>

#include <sys/stat.h>

using namespace std;

// Four CC values for magic codes
inline uint32_t FOURCC(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    return ( (uint32_t) (((d)<<24) | (uint32_t(c)<<16) | (uint32_t(b)<<8) | uint32_t(a)) );
}

inline uint32_t getFourCC(const char *code)
{
    return ((uint32_t)code[3] << 24) |
           ((uint32_t)code[2] << 16) |
           ((uint32_t)code[1] << 8)  |
           ((uint32_t)code[0]);
}

inline char *strFourCC(uint32_t code)
{
	static char str[5];

	str[0] = char(code >> 24);
	str[1] = char(code >> 16);
	str[2] = char(code >> 8);
	str[3] = char(code);
	str[4] = '\n';

	return str;
}

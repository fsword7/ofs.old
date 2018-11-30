/*
 * image.h
 *
 *  Created on: Nov 30, 2018
 *      Author: Tim Stark
 */

#pragma once

class Image {
public:
	Image(int w, int h, int fmt, int mips = 1);
	~Image();

	inline int getWidth()     { return width; }
	inline int getHeight()    { return height; }
	inline int getFormat()    { return format; }
	inline uint8_t *getData() { return data; }
	inline int getSize()      { return size; }

    bool     isCompressed() const;
    int      getMipLevelSize(int mip) const;
    uint8_t *getMipLevel(int mip);

protected:
	inline int pad(int n) const { return (n + 3) & ~0x3; };

    int getComponents(int fmt) const;
    int getMipLevelSize(int w, int h, int mip, int fmt) const;

private:
	int width;
	int height;
	int pitch;
	int mipLevels;
	int components;
	int format;
	int size;
	uint8_t *data;
};

/*
 * texture.h
 *
 *  Created on: Jul 28, 2019
 *      Author: Tim Stark
 */

#pragma once

class Texture
{
public:
	Texture(int w, int h, int mips = 1);
	virtual ~Texture();

	inline int getWidth()  { return width; }
	inline int getHeight() { return height; }
	inline int getDepth()  { return depth; }
	inline int getPitch()  { return pitch; }
	inline int getSize()   { return size; }

	inline uint8_t *getData() { return data; }

	inline int pad(int n) const { return (n + 3) & ~0x03; }

	// MipMapping function calls
	uint8_t *getMipData(int lod);
	int getMipDataSize(int lod) const;

	virtual bool setFormat(int fmt) = 0;
	virtual void bind() = 0;

	enum AddressMode {
		Wrap = 0,
		BorderClamp = 1,
		EdgeClamp = 2
	};

	enum MipMapMode {
		NoMipMaps = 0,
		FixedMipMaps = 1,
		AutoMipMaps = 2
	};

protected:
	// Virtual function calls
	virtual int getComponents(int format) const = 0;
	virtual int getFormat() const = 0;

	virtual int getMipSize(int fmt, int w, int h, int lod) const = 0;


protected:
	int		width, height;
	int		depth;
	int		pitch = 0;
	int		size = 0;

	int		format = 0;
	int		components = 0;

	bool	initFlag = false;

	// MIP levels for LOD
	int		mipLevels;

	// Image data
	uint8_t *data = nullptr;
};

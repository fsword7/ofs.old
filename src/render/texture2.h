/*
 * texture2.h
 *
 *  Created on: Jul 28, 2019
 *      Author: Tim Stark
 */

#pragma once

class Texture2
{
public:
	Texture2() = default;
	virtual ~Texture2() = default;

	inline int getWidth()  { return width; }
	inline int getHeight() { return height; }
	inline int getDepth()  { return depth; }
	inline int getPitch()  { return pitch; }

	inline uint8_t *getData() { return data; }

	inline int pad(int n) { return (n + 3) & ~0x03; }

	// MipMapping function calls
	uint8_t *getMipData(int lod);
	int getMipSize(int lod);

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

	virtual int getMipSize(int w, int h, int mip) const = 0;

protected:
	int		width, height;
	int		depth;
	int		pitch;
	int		size;

	// MIP levels for LOD
	int		mipLevels;

	// Image data
	uint8_t *data = nullptr;
};

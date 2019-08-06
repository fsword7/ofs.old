/*
 * texture.h
 *
 *  Created on: Aug 5, 2019
 *      Author: Tim Stark
 */

#include <GL/glew.h>
#include "render/texture.h"

class glTexture : public Texture
{
public:
	glTexture(int h, int w, int mips = 1);
//	glTexture(int h, int w, int d, int mips = 1);
	~glTexture();

	bool isCompressed() const;

	bool setFormat(int fmt);
	void load(int target);
	void bind();

protected:
	int getComponents(int format) const;
	int getFormat() const;
	int getBorderAddress() const;

	int getMipSize(int fmt, int w, int h, int mip) const;
	int getMipDataSize2(int lod) const;

	void loadMipData(int target);

private:
	int glName = 0;
};

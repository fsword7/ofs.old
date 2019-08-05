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
	glTexture(int fmt, int h, int w, int mips = 1);
//	glTexture(int fmt, int h, int w, int d, int mips = 1);
	~glTexture();

	void load(int target);
	void bind();

protected:
	int getComponents(int format) const;
	int getFormat() const;

	int getMipSize(int fmt, int w, int h, int mip) const;


private:
	int glName = 0;
};

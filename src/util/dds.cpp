/*
 * dds.cpp
 *
 *  Created on: Jul 23, 2019
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "render/image.h"
#include "util/dds.h"

#include <GL/glew.h>

Image *ddsLoader::load(std::string& fname)
{
	uint8_t  *data;
	uint32_t size;
	Image    *img;

	std::ifstream ddsFile(fname, std::ios::binary|std::ios::in);
	if (!ddsFile.is_open())
		return nullptr;

	ddsFile.seekg(0, std::ios::end);
	size = ddsFile.tellg();
	ddsFile.seekg(0, std::ios::beg);

	data = new uint8_t[size];
	ddsFile.read((char *)data, size);

	img = load(data, size);
	delete []data;

	return img;
}

Image *ddsLoader::load(uint8_t *data, uint32_t size)
{
    Image *img = nullptr;
    uint8_t *ptr = data;
    ddsHeader *hdr;
    int glFormat = -1;

    hdr = (ddsHeader *)ptr;

    // Check validation
    if (hdr->dwMagic != getFourCC("DDS ") ||
        hdr->dwSize != sizeof(ddsHeader) - sizeof(uint32_t)) {
        std::cerr << "*** Bad DDS header - aborted." << std::endl;
        return nullptr;
    }
    ptr += sizeof(ddsHeader);

    if (hdr->ddpf.dwFourCC != 0) {
        char fourCC[5];

        *(uint32_t *)&fourCC = hdr->ddpf.dwFourCC;
        fourCC[4] = '\0';

//        std::cout << "DDS Format Code: " << fourCC << std::endl;

        if (hdr->ddpf.dwFourCC == getFourCC("DXT1")) {
            glFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        } else if (hdr->ddpf.dwFourCC == getFourCC("DXT3")) {
            glFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        } else if (hdr->ddpf.dwFourCC == getFourCC("DXT5")) {
            glFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        } else {
            std::cerr << "*** Unknown DDS format code: " << fourCC << std::endl;
            return nullptr;
        }
    }

    img = new Image(hdr->dwWidth, hdr->dwHeight, glFormat, std::max((int)hdr->dwMipMapCount, 1));
    if (img == nullptr)
        return nullptr;
    std::copy(ptr, ptr+img->getSize(), img->getData());

//    std::cout << "Image: " << hdr->dwWidth << " X " << hdr->dwHeight << " Depth: " << hdr->dwDepth
//              << "  MIP Levels: " << hdr->dwMipMapCount << std::endl;
//    std::cout << "  Size: " << img->getSize() << " bytes" << std::endl;

    return img;
}




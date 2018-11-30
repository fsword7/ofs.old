/*
 * ztreeamgr.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: Tim Stark
 */

#include "main/main.h"
#include "render/ztreemgr.h"

#include <unistd.h>
#include <zlib.h>

zTreeManager::zTreeManager()
{
}

zTreeManager::~zTreeManager()
{
    if (data.is_open())
		data.close();
}

bool zTreeManager::open(std::string fname)
{
    std::cout << "Opening file..." << std::endl;
	data.open(fname.c_str(), std::ios::in|std::ios::binary);
	if (!data.is_open())
		return false;

    data.seekg(0, data.end);
    auto fileSize = data.tellg();
    data.seekg(0, data.beg);
//    std::cout << "File size: " << fileSize << " bytes" << std::endl;


    std::cout << "Reading header block..." << std::endl;
	data.read((char *)&hdr, sizeof(hdr));
	if (data.fail()) {
		data.close();
		return false;
	}
//    if (hdr.magic == FOURCC('T','X', 1, 0))
//        std::cout << "Magic - Good" << std::endl;
//    if (hdr.size == sizeof(hdr))
//        std::cout << "Size - Good" << std::endl;
//    if (hdr.dataLength+hdr.dataOfs == fileSize)
//        std::cout << "File size - Good" << std::endl;

    // Validate header block
    if (hdr.magic != FOURCC('T', 'X', 1, 0) || hdr.size != sizeof(hdr) ||
        hdr.dataLength+hdr.dataOfs != fileSize) {
        data.close();
        return false;
    }


    std::cout << "Reading TOC block..." << std::endl;
    nodes = new zTreeNode[hdr.nodeCount];
    data.read((char *)nodes, sizeof(zTreeNode)*hdr.nodeCount);
    if (data.fail()) {
        data.close();

        if (nodes != nullptr)
            delete []nodes;
        nodes = nullptr;

        return false;
    }
//    std::cout << "TOC block: " << sizeof(zTreeNode)*hdr.nodeCount << " vs " << hdr.dataOfs - sizeof(hdr) << std::endl;

    std::cout << "Number of nodes: " << hdr.nodeCount << " data offset: " << hdr.dataOfs << std::endl;


    std::cout << "All done..." << std::endl;
	this->fname = fname;
	return true;
}

zTreeManager *zTreeManager::create(std::string pname, std::string tname)
{
	zTreeManager *ztree = new zTreeManager();
	std::string fname = pname + "/" + tname + ".tree";

//    char *dir = getcwd(NULL, 0);
//    std::cerr << "Current directory: " << dir << std::endl;
//    if (chdir(pname.c_str()))
//        std::cerr << "Changing directory: " << strerror(errno) << std::endl;
//    dir = getcwd(NULL, 0);
//    std::cerr << "Current directory: " << dir << std::endl;


    std::cout << "Loading terrain data file: \"" << fname << "\"" << std::endl;
	if (!ztree->open(fname)) {
		std::cerr << "*** I/O Error: " << strerror(errno) << std::endl;
		delete ztree;
		return nullptr;
	}

	return ztree;
}

uint32_t zTreeManager::getDeflatedSize(uint32_t idx)
{
    return uint32_t(((idx < hdr.nodeCount-1) ? nodes[idx+1].pos : hdr.dataLength) - nodes[idx].pos);
}

uint32_t zTreeManager::getInflatedSize(uint32_t idx)
{
    return nodes[idx].size;
}

uint32_t zTreeManager::index(int lod, int lat, int lng)
{
    switch (lod) {
        case 1:
            return hdr.rootPos1;
        case 2:
            return hdr.rootPos2;
        case 3:
            return hdr.rootPos3;
        case 4:
            return hdr.rootPos4[lng];
        default:
            uint32_t pidx = index(lod-1, lat/2, lng/2);
            if (pidx == ZTREE_NIL)
                return ZTREE_NIL;
            int cidx = ((lat&1) << 1) | (lng&1);
//            std::cout << "Index LOD: " << lod << " (" << lat << "," << lng << ") Index: " << cidx << std::endl;
            return nodes[pidx].child[cidx];
    }
}

int zTreeManager::inflateData(uint8_t *zdata, uint32_t zsize, uint8_t *udata, uint32_t usize)
{
    z_stream zinfo = {0};
    int nerr, nret = -1;

    zinfo.zalloc = Z_NULL;
    zinfo.zfree = Z_NULL;
    zinfo.opaque = Z_NULL;

    zinfo.next_in = zdata;
    zinfo.avail_in = zsize;

    zinfo.next_out = udata;
    zinfo.avail_out = usize;

    nerr = inflateInit(&zinfo);
    if (nerr == Z_OK) {
        nerr = inflate(&zinfo, Z_FINISH);
        if (nerr == Z_STREAM_END)
            nret = (int)zinfo.total_out;
    }
    inflateEnd(&zinfo);

    return nret;
}

int zTreeManager::read(int lod, int lat, int lng, uint8_t **outData)
{
    uint32_t  idx = index(lod, lat, lng);
    uint8_t  *zdata, *udata;
    uint32_t  zsize, usize;
    int       res;

    if (idx == ZTREE_NIL) {
//        std::cout << "Tile (" << lat << "," << lng << ") LOD " << lod
//                  << ": Image not found - aborted." << std::endl;
        *outData = nullptr;
        return 0;
    }

    zsize = getDeflatedSize(idx);
    if (zsize == 0) {
//        std::cout << "Tile (" << lat << "," << lng << ") LOD " << lod
//                  << ": Contains null data." << std::endl;
        *outData = nullptr;
        return 0;
    }
    usize = getInflatedSize(idx);


    zdata = new uint8_t[zsize];
    udata = new uint8_t[usize];

    data.seekg(nodes[idx].pos + hdr.dataOfs, data.beg);
    data.read((char *)zdata, zsize);
    res = inflateData(zdata, zsize, udata, usize);

//    std::cout << "Node #" << idx << " File position: " << nodes[idx].pos << std::endl;
//    std::cout << "  Data size: " << zsize << " bytes (uncompressed " << usize << " bytes)" << std::endl;
//    std::cout << "Successfully uncompressed " << res << " bytes." << std::endl;

    if (res != usize) {
        delete []udata;
        udata = nullptr;
    }
    delete []zdata;

    *outData = udata;
    return res;
}


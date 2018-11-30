/*
 * ztreemgr.h
 *
 *  Created on: Nov 30, 2018
 *      Author: Tim Stark
 */

#pragma once

#define ZTREE_NIL uint32_t(-1)

struct zTreeHeader {
	uint32_t  magic;       // File ID and version - { 'T', 'X', 1, 0 }
	uint32_t  size;        // Header size (bytes)
	uint32_t  flags;       // flags
	uint32_t  dataOfs;     // Data block offset (header + TOC)
	uint64_t  dataLength;  // Length of compressed data block
	uint32_t  nodeCount;   // Number of tree nodes
	uint32_t  rootPos1;    // Index of LOD 0 tile
	uint32_t  rootPos2;    // Index of LOD 1 tile
	uint32_t  rootPos3;    // Index of LOD 2 tile
	uint32_t  rootPos4[2]; // Index of LOD 3 tiles (two tiles)
};

struct zTreeNode {
	uint64_t  pos;          // File position of node data
	uint32_t  size;         // Data block length (bytes)
	uint32_t  child[4];     // Index position of child nodes.

	zTreeNode(): pos(0), size(0) {
		for (int idx = 0; idx < 4; idx++)
            child[idx] = ZTREE_NIL;
	}
};

class zTreeTOC {
public:
	zTreeTOC();
	~zTreeTOC();
};

class zTreeManager {
public:
	zTreeManager();
	~zTreeManager();

	static zTreeManager *create(std::string fname, std::string type);

	bool open(std::string fname);
    int read(int lod, int lat, int lng, uint8_t **data);

protected:
    uint32_t index(int lod, int lat, int lng);
    uint32_t getDeflatedSize(uint32_t idx);
    uint32_t getInflatedSize(uint32_t idx);
    int inflateData(uint8_t *zdata, uint32_t zsize, uint8_t *udata, uint32_t usize);

private:
	std::string fname;

	std::ifstream data;

	zTreeHeader hdr;
    zTreeNode  *nodes;
};

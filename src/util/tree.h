/*
 * tree.h
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

#define QTREE_NODES	4	// Quadtree structure
#define OTREE_NODES 8	// Octree structure

class QuadTree {

private:
	QuadTree *nodes[QTREE_NODES];
};

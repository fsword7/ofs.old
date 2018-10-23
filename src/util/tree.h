/*
 * tree.h
 *
 *  Created on: Oct 14, 2018
 *      Author: Tim Stark
 */

#pragma once

#define QTREE_NODES	4	// Quadtree structure
#define OTREE_NODES 8	// Octree structure

template<int nodes>
class Tree
{
public:
	Tree(Tree *parent = nullptr);
	~Tree();

	Tree *getChild(int idx);
	const Tree *getChild(int idx) const;

	Tree *addChild(int idx, Tree *child);
	bool delChild(int idx);
	bool delChildren();

private:
	Tree *parent;
	Tree *child[nodes];
};

template<int nodes>
Tree<nodes>::Tree(Tree *_parent)
{
	parent = _parent;
	for (int idx = 0; idx < nodes; idx++)
		child[idx] = nullptr;
}

template<int nodes>
Tree<nodes>::~Tree()
{
	if (parent != nullptr)
		parent = nullptr;
	for (int idx = 0; idx < QTREE_NODES; idx++)
		if (child[idx] != nullptr)
			delete child[idx];
}

template<int nodes>
Tree<nodes> *Tree<nodes>::getChild(int idx)
{
	if (idx < 0 || idx >= QTREE_NODES)
		return nullptr;
	return child[idx];
}

template<int nodes>
const Tree<nodes> *Tree<nodes>::getChild(int idx) const
{
	if (idx < 0 || idx >= QTREE_NODES)
		return nullptr;
	return child[idx];
}

template<int nodes>
Tree<nodes> *Tree<nodes>::addChild(int idx, Tree *_child)
{
	if (idx < 0 || idx >= QTREE_NODES)
		return nullptr;
	child[idx] = _child;

	return child[idx];
}

template<int nodes>
bool Tree<nodes>::delChild(int idx)
{
	if (idx < 0 || idx >= QTREE_NODES)
		return false;
	if (child[idx] != nullptr) {
		delete child[idx];
		child[idx] = nullptr;
		return true;
	}
	return false;
}

template<int nodes>
bool Tree<nodes>::delChildren()
{
	bool ok = true;
	for (int idx = 0; idx < QTREE_NODES; idx++) {
		if (child[idx] != nullptr) {
			if (child[idx]->delChildren() == true) {
				delete child[idx];
				child[idx] = nullptr;
			} else
				ok = false;
		}
	}
	return ok;
}

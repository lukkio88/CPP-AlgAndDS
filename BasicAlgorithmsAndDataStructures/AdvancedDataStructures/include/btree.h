#pragma once
#ifndef __BTREE_H
#define __BTREE_H

template<int B>
struct BTreeNode {

	BTreeNode() {
		for (auto i = 0; i < 2 * B; ++i)
			child[i] = nullptr;
		n = 0;
		leaf = true;
	}

	int key[2 * B - 1];
	BTreeNode * child[2 * B];
	int n;
	bool leaf;
};

template<int B>
class BTree {
public:
	BTree();
	BTreeNode<B>* search(const int & k, int & i);
	void insert(const int & k);
private:
	void splitChild(BTreeNode<B> * x, const int & i);
	void insertNonEmpty(const int & i);
private:
	BTreeNode<B> * root;
};

#endif
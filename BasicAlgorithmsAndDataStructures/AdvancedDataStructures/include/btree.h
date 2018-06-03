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

	//insertion helpers
	void splitChild(const int & childIdx);
	void insertNonEmpty(const int & key);

	//deletion helpers
	int findKey(const int & k);
	bool remove(const int & k);
	void removeFromLeaf(const int & kIdx);
	void removeFromInternal(const int & kIdx);
	void findPrev(const int & kIdx);
	void findSucc(const int & kIdx);
	void borrowFromLeft(const int & childIdx);
	void borrowFromRight(const int & childIdx);
	void merge(const int & childIdx);

	int key[2 * B - 1];
	BTreeNode * child[2 * B];
	int n;
	bool leaf;
};

template<int B>
class BTree {
public:
private:
private:
	BTreeNode<B> * root;
};

#endif
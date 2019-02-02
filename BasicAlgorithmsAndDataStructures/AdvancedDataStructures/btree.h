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
	void insert(const int & newKey);
	void splitChild(const int & childIdx);
	void insertNonFull(const int & key);

	//deletion helpers
	int findKey(const int & k);
	bool remove(const int k);
	void removeFromLeaf(const int & kIdx);
	BTreeNode<B>* removeFromInternal(const int & kIdx, int & kUpdated);
	BTreeNode<B> * findPrev(const int & kIdx, int & idxPrev);
	BTreeNode<B> * findSucc(const int & kIdx, int & idxNext);
	void borrowFromLeft(const int & childIdx);
	void borrowFromRight(const int & childIdx);
	void merge(const int & childIdx);

	int key[2 * B - 1];
	BTreeNode<B> * child[2 * B];
	int n;
	bool leaf;
};

template<int B>
class BTree {
public:
	BTree();
	~BTree();
	void insertKey(const int & newKey);
	void deleteKey(const int & key);
private:
	BTreeNode<B> * root;
};

#endif
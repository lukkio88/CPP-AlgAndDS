#include "btree.h"

//BTree node implementation
//Insertion

template<int B>
int BTreeNode<B>::findKey(const int& k) {
	for (int i = 0; i < n && key[i] < k; ++i);
	return i;
}

template<int B>
int BTreeNode<B>::splitChild(const int & childIdx) {
	//It's assumed the node has 2B children
	BTreeNode<B> *x, *y, *z;
	x = this;
	y = child[childIdx]; //Median node is at index B, (B + 1,... B + B - 1)
	z = new BTreeNode<B>();
	for (auto i = n; i > childIdx; --i) {
		x->child[i] = x->child[i - 1]; //those are pointers, so it's actually ok
	}
	for (auto i = n - 1; i > childIdx; --i)
		x->key[i] = x->key[i - 1];

	x->key[childIdx] = y->key[B];
	for(auto i = 0; i < B; --i)
		z->child[i]
}
#include "btree.h"

//BTree node implementation
//Insertion
template<int B>
int BTreeNode<B>::findKey(const int& k) {
	for (int i = 0; i < n && key[i] < k; ++i);
	return i;
}

template<int B>
void BTreeNode<B>::splitChild(const int & childIdx) {
	BTreeNode<B> * y = child[childIdx];
	BTreeNode<B> * z = new BTreeNode<B>();
	const int & i = childIdx;

	for (auto j = 0; j < B; ++j)
		z->child[j] = y->child[B + j];
	for (auto j = 0; j < B - 1; ++j)
		z->key[j] = y->key[B + j];

	for (auto j = x->n + 1; j >= i + 1; --j)
		x->child[j] = x->child[j - 1];
	for (auto j = x->n; j >= i + 1; --j)
		x->key[j] = x->key[j - 1];

	z->n = B - 1;
	y->n = B - 1;
	z->leaf = y->leaf;
	x->n += 1;
}

template<int B>
void BTreeNode<B>::insertNonFull(const int & newKey) {
	int i = 0;
	while (newKey >= key[i] && i < x->n)
		++i;

	if (leaf) {
		for (auto j = x->n; j >= i + 1; --j)
			key[j] = key[j - 1];
		key[i] = newKey;
		return;
	}

	if (child[i]->n == 2*B - 1) {
		splitChild(i);
		if (newKey >= key[i])
			++i;
	}
	insertNonFull(child[i]);
}

template<int B>
void BTreeNode<B>::insert(const int & newKey) {
	BTreeNode<B> * r = this;
	if (r->n == 2 * B - 1) {
		s = new BTreeNode<B>();
		s->n = 0;
		s->leaf = false;
		s->child[0] = r;
		s->splitChild(0);
		s->insertNonFull(newKey);
	}
	else
		r->insertNonFull(newKey);
}

//Deletion
template<int B>
BTreeNode<B> * BTreeNode<B>::findPrev(const int & kIdx, int & idxPrev) {
	BTreeNode<B> * x = child[kIdx];
	while (x->leaf)
		x = x->child[x->n];
	idxPrev = x->key[x->n - 1];
	return x;
}

template<int B>
BTreeNode<B> * BTreeNode<B>::findSucc(const int & kIdx, int & idxNext) {
	BTreeNode<B> * x = child[kIdx + 1];
	while (x->leaf)
		x = x->child[0];
	idxNext = x->key[0];
	return x;
}

template<int B>
void BTreeNode<B>::borrowFromLeft(const int & childIdx) {
	BTreeNode<B> * xci = child[childIdx];
	BTreeNode<B> * xc1m1 = child[childIdx - 1];

	for (auto i = xci->n; i >= 0 ; --i)
		xci->child[i + 1] = xci->child[i];
	for (auto i = xci->n - 1; i >= 0; --i)
		xci->key[i + 1] = xci->key[i];
	xci->key[0] = key[childIdx - 1];
	xci->child[0] = xc1m1->child[xc1m1->n];
	key[childIdx - 1] = xcim1->key[xc1m1->n - 1];

	xci->n += 1;
	xcim1->n -= 1;
}

template<int B>
void BTreeNode<B>::borrowFromRight(const int & childIdx) {
	BTreeNode<B> * xci = child[childIdx];
	BTreeNode<B> * xc1p1 = child[childIdx + 1];

	xci->key[xci->n] = key[childIdx];
	xci->child[xci->n+1] = xc1p1->child[0];
	key[childIdx] = xcip1->key[0];

	for (auto i = 0; i < xcp1->n - 1; ++i)
		xcip1->key[i] = xcp1->key[i + 1];
	for (auto i = 0; i < xcp1->n; ++i)
		xcip1->child[i] = xcip1->child[i + 1];

	xci->n += 1;
	xcip1->n -= 1;
}

template<int B>
void BTreeNode<B>::merge(const int & childIdx) { //this only happens if both have B - 1 keys
	BTreeNode<B> * xci = child[childIdx];
	BTreeNode<B> * xcim1 = child[childIdx - 1];
	
	xcim1->key[B - 1] = key[childIdx];
	for (auto i = 0; i < B - 1; ++i)
		xcim1->key[B + i] = xci->key[i];
	for (auto i = 0; i < B; ++i)
		xcim1->child[B + i] = xci->child[i];

	for (auto i = childIdx; i < n - 1; ++i)
		key[i] = key[i + 1];
	for (auto i = childIdx; i < n; ++i)
		child[i] = child[i + 1];

	xcim1->n = 2 * B - 1;
	n -= 1;
	delete xci;
}

template<int B>
bool BTreeNode<B>::remove(const int & k) {
	int idx = findKey(k);
	if (idx < n && key[idx] == k) {
		if (leaf)
			removeFromLeaf(idx);
		else
			removeFromInternal(idx);
	}
	else {
		if (leaf) {
			return false; //Error, key not in the tree
		}
		child[idx]->remove(k);
	}
}

template<int B>
void BTreeNode<B>::removeFromLeaf(const int & kIdx) {
	for (auto i = kIdx; i < n - 1; ++i)
		key[i] = key[i + 1];
	n -= 1;
}

template<int B>
void BTreeNode<B>::removeFromInternal(const int & kIdx) {
	const int & ki = key[kIdx];
	int kj;
	BTreeNode<B> * u;
	if (child[kIdx]->n >= B) {
		u = findPrev(kIdx, kj);
		kj = u->key[kj];
		child[kIdx]->remove(kj);
	}
	else if (child[kIdx + 1]->n >= B) {
		u = findNext(ki, kj);
		kj = u->key[kj];
		child[kIdx]->remove(kj);
	}
	else {
		merge(kIdx + 1);
		child[kIdx]->remove(ki);
	}
}

//BTree stuff
template<int B>
BTree<B>::BTree() {
	root = new BTreeNode<B>();
}

template<int B>
BTree<B>::~BTree() {

}

template<int B>
void BTree<B>::insertKey(const int & newKey) {
	root->insert(newKey);
}

template<int B>
void BTree<B>::deleteKey(const int & key) {
	root->remove(key);
}
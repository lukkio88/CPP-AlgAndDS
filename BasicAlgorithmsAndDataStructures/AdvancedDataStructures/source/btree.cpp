#include <btree.h>

template<int B>
BTree<B>::BTree() {
	root = nullptr;
}

template<int B>
BTreeNode<B> * search(const int& k, const int & idx) {
	BTreeNode<B> * x = root;
	int i = 0;
	while (x != nullptr) {
		while (i < x->n && k > x->key[i])
			--i;
		if (i < x->n &&  k == x->key[i]) {
			idx = i;
			break;
		}
		x = x->child[i];
	}
	return x;
}

template<int B>
void splitChild(BTreeNode<B> * x, const int& i) {
	BTreeNode<B> 
		* y = x->child[i], 
		* z = new BTreeNode<B>();
	for (auto j = 0; j < B - 1; ++j)
		z->key[j] = y->key[j + B];
	if (!y->leaf)
		for (auto j = 0; j < B; ++j)
			z->child[j] = y->child[j + B];
	y->n = B - 1;
	z->n = B - 1;
	for (j = x->n; j >= i + 1; --j)
		x->key[j] = x->key[j - 1];
	x->key[i] = y->key[B - 1];
	for (j = x->n + 1; j >= i + 2; --j)
		x->child[j] = x->child[j - 1];
	x->child[i + 1] = z;
	++x->n;
}

template<int B>
void insertNonFull(BTreeNode<B> * x, const int & k) {
	int i;
	while (!x->leaf) {
		i = x->n - 1;
		while (i >= 0 && k < x->key[i])
			--i;
		++i;
		if (x->child[i]->n == 2 * B - 1) {
			splitChild(x, i);
			if (k > x->key[i])
				++i;
		}
		x = x->child[i];
	}
	i = x->n - 1;
	while (i >= 0 && k < x->key[i]) {
		x->key[i + 1] = x->key[i];
		--i;
	}
	++i;
	x->key[i] = k;
	++x->n;
}

template<int B>
void insert(const int & k) {
	BTreeNode<B> * r = root;
	if (r->n == 2 * B - 1) {
		BTreeNode<B> * s = new BTreeNode<B>();
		s->leaf = false;
		s->n = 0;
		s->child[0] = r;
		splitChild(s, 0);
		insertNonFull(s, k);
	}
	insertNonFull(r, k);
}
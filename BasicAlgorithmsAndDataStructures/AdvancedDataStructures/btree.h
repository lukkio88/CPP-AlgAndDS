#pragma once

template<typename K, int B>
struct BTreeNode {
	int n;
	K k[2 * B - 1];
	BTreeNode * child[2 * B];
	bool leaf;
	BTreeNode() {
		for (auto j = 0; j < 2 * B; ++j)
			child[j] = nullptr;
		n = 0;
		leaf = true;
	}
};

template<typename K, int B>
class BTree {
public:
	BTree(int (*cmp)(const K&, const K&));
	BTreeNode<K, B>* search(const K & k);
	void insert(const K& k);
private:
	void splitchild(BTreeNode<K, B> * x,const int& i);
	void insertNonFull(const K& k);
private:
	BTreeNode<K,B> * root;
	int(*compare)(const K&, const K&);
};

template<typename K, int B>
BTree<K,B>::BTree(int (*cmp)(const K&, const K&)) {
	root = new BTreeNode<K,B>();
	leaf = true;
	root->n = 0;
	compare = cmp;
}

template<typename K, typename V, int B>
BTreeNode<K, V, B>* BTree<K, V, B>::search(const K & k) {
	BTreeNode<K, V, B>* x = root;
	int i;
	while (x != nullptr) {
		i = 0;
		while (i < n && compare(k, x->k[i]) < 0) {
			++i;
		}
		if (i < n && compare(k, x->k[i])) {
			break;
		} else {
			x = x->child[i];
		}
	}
	return x;
}

//The following assumes y has 2B children
template<typename K, typename V, int B>
void BTree<K,V,B>::splitchild(BTreeNode<K, V, B> * x,const K& i) {
	BTreeNode<K, V, B> *z, *y;
	z = new BTreeNode<K, V, B>();
	//Let's manipulate y and z first
	for (auto j = y->n - 2; j >= 0; --j)
		z->key[j] = y->key[j+B];
	if (!y->leaf)
		for (auto j = y->n - 1; j >= 0; --j)
			z->child[j] = y->child[j + B];
	y->n = B - 1;
	for (auto j = x->n; j >= i + 1; --j)
		x->childj] = x->child[j - 1];
	for (auto j = x->n; j >= i + 1; --j)
		x->key[j] = x->key[j - 1];
	x->key[j] = y->key[B - 1];
	++x->n;
}

template<typename K, typename V, int B>
void BTree<K, V, B>::insert(BTreeNode<K, V, B> *x) {
	BTreeNode<K, V, B> * r = root;
	if (r->n == 2 * B - 1) {
		BTreeNode<K, V, B> * s = new BTreeNode<K, V, B>();
		root = s;
		s->leaf = false;
		s->n = 0;
		s->child[0] = r;
		splitchild(s, 0);
	}
	insertNonFull(x);
}

template<typename K, typename V, int B>
void BTree<K,V,B>::insertNonFull(BTreeNode<K, V, B> * z) {
	auto i = x->n;
	BTree<K, V, B> * x = root;
	if (x->leaf == true) {
		while (i >= 0 && compare(z->key, x->key)) {
			x->key[i + 1] = x->key[i];
			--i;
		}
		x->key[i + 1] = z->key;
	}
}
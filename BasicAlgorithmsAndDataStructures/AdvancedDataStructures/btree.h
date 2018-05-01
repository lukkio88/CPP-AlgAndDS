#pragma once

template<typename K, typename V, int B>
struct BTreeNode {
	int n;
	K k[2 * B - 1];
	BTreeNode * child[2 * B];
	bool leaf;
};

template<typename K, typename V, int B>
class BTree {
public:
	BTree(int (*cmp)(const K&, const K&));
private:
	void splitChild(BTreeNode<K, V, B> * x, K i);
private:
	BTreeNode<K,V,B> * root;
	int(*compare)(const K&, const K&);
};

template<typename K, typename V, int B>
BTree::BTree(int (*cmp)(const K&, const K&)) {
	root = new BTreeNode<K,V,B>();
	leaf = true;
	root->n = 0;
	compare = cmp;
}

template<typename K, typename V, int B>
void BTree::splitchild(BTreeNode<K, V, B> * x, K i) {
	BTreeNode<K, V, B> * z = new BTree<K, V, B>();
	BTreeNode<K, V, B> * y = x[i];
	z->n = B - 1;
	for (j = 0; j < B - 1; ++j)
		z->key[j] = y->key[j + 1];
	if (!y->leaf)
		for (auto j = 0; j < B - 1; ++j)
			z->child[j] = y->child[j + 1];
	y->n = B - 1;
	for (auto j = x->n; j >= i; --j)
		x->c[j + 1] = x->c[j];
	x->c[i] = z;
}
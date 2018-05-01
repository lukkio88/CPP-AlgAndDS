#pragma once
#ifndef __BSTREE_H
#define __BSTREE_H

template<typename K>
struct TreeNode {
	K k;
	TreeNode<K> * left, *right, *parent;
};

template<typename K>
TreeNode<K> * minimum(TreeNode<K> * x);

template<typename K>
TreeNode<K> * maximum(TreeNode<K> * x);

template<typename K>
class BSTree {
public:
	BSTree(int (*_compare)(const K&,const K&));
	void insert(TreeNode<K> * x);
	TreeNode<K> *  search(const K & key);
	void remove(TreeNode<K> * x);
private:
	void transplant(TreeNode<K> * x, TreeNode<K> * y);
private:
	int(*compare)(const K&, const K&);
	TreeNode<K> * root;
};

template<typename K>
TreeNode<K> * minimum(TreeNode<K> * x) {
	TreeNode<K> * y = x;
	while (y->left != nullptr) y = y->left;
	return y;
}

template<typename K>
TreeNode<K> * maximum(TreeNode<K> * x) {
	TreeNode<K> * y = x;
	while (y->right != nullptr) y = y->right;
	return y;
}

template<typename K>
BSTree<K>::BSTree(int(*_compare)(const K&, const K&)) {
	compare = _compare;
	root = nullptr;
}

template<typename K>
void BSTree<K>::insert(TreeNode<K> * x) {
	if (root == nullptr) {
		root = x;
		x->parent = nullptr;
	}
	else {
		TreeNode<K> * y = nullptr;
		TreeNode<K> * z = root;
		while (z != nullptr) {
			y = z;
			if (compare(x->key,z->key) < 0) {
				z = z->left;
			}
			else {
				z = z->right;
			}
		}
		if (x->key < y->key) {
			y->left = x;
		}
		else {
			y->right = x;
		}
		x->parent = y;
	}
	x->left = x->right = nullptr;
}

template<typename K>
TreeNode<K> *  BSTree<K>::search(const K & key) {
	if (root == nullptr) return nullptr;
	else {
		TreeNode * x = root;
		while (x != nullptr && compare(key,x->key) != 0) {
			if (compare(key,x->key) < 0 ) x = x->left;
			else x = x->right;
		}
		return x;
	}
}

template<typename K>
void BSTree<K>::remove(TreeNode<K> * x) {
	if (x->left == nullptr) {
		transplant(x, x->right);
	}
	else if (x->right == nullptr) {
		transplant(x, x->left);
	}
	else {
		TreeNode<K> * y = minimum(x->right);
		if (y->parent != x) {
			transplant(y, y->right);
			y->right = x->right;
			y->right->parent = y;
		}
		transplant(x, y);
		y->left = x->left;
		y->left->parent = y;
	}
}

template<typename K>
void BSTree<K>::transplant(TreeNode<K> * x, TreeNode<K> * y) {
	if (x == root) {
		root = y;
	}
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	if (y != nullptr) {
		y->parent = x->parent;
	}
}

#endif
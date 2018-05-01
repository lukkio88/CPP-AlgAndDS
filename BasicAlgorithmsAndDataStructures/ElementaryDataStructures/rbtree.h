#pragma once
#ifndef __RBTREE_H
#define __RBTREE_H

constexpr int BLACK = 0;
constexpr int RED = 1;

template<typename K>
struct RBTreeNode {
	K key;
	bool color;
	RBTreeNode<K> * left, *right, *parent;
};

template<typename K>
RBTreeNode<K> * minimum(RBTreeNode<K> * x, RBTreeNode<K> * nil);

template<typename K>
RBTreeNode<K> * maximum(RBTreeNode<K> * x, RBTreeNode<K> * nil);

template<typename K>
class RBTree {
public:
	RBTree(int(*_compare)(const K &, const K &));
	void insert(RBTreeNode<K> * x);
	RBTreeNode<K> * search(const K & key);
	void remove(RBTreeNode<K> * x);
private:
	void transplant(RBTreeNode<K> * x, RBTreeNode<K> * y);
	void leftRotate(RBTreeNode<K> * x);
	void rightRotate(RBTreeNode<K> * x);
	void rbInsertFixup(RBTreeNode<K> * x);
	void rbDeleteFixup(RBTreeNode<K> * x);
private:
	int(*compare)(const K &, const K &);
	RBTreeNode<K> sentinel;
	RBTreeNode<K> * root;
};

template<typename K>
RBTree<K>::RBTree(int(*_compare)(const K &, const K &)) {
	compare = _compare;
	sentinel.parent = &sentinel;
	sentinel.left = &sentinel;
	sentinel.right = &sentinel;
	root = &sentinel;
}

template<typename K>
RBTreeNode<K> * minimum(RBTreeNode<K> * x, RBTreeNode<K> * nil) {
	while (x->left != nil) x = x->left;
	return x;
}

template<typename K>
RBTreeNode<K> * maximum(RBTreeNode<K> * x, RBTreeNode<K> * nil) {
	while (x->right != nil) x = x->right;
	return x;
}

template<typename K>
void RBTree<K>::insert(RBTreeNode<K> * x) {
	RBTreeNode<K> * nil = &sentinel;
	RBTreeNode<K> * z, *y;
	z = root;
	y = nil;
	while (z != nil) {
		y = z;
		if (compare(x->key, z->key) < 0) z = z->left;
		else z = z->right;
	}
	if (x == y->left)
		y->left = x;
	else
		y->right = x;
	x->parent = y;
	x->color = RED;
	if (y->color == RED) rbInsertFixup(x);
}

template<typename K>
RBTreeNode<K> * RBTree<K>::search(const K & key) {
	RBTreeNode<K> * nil = &sentinel;
	RBTreeNode<K> * x = root;
	while (x != nil && compare(key,x->key) != 0) {
		if (compare(key, x->key) < 0) x = x->left;
		else x = x->right;
	}
	return x;
}

template<typename K>
void RBTree<K>::remove(RBTreeNode<K> * x) {
	RBTreeNode<K> * nil = &sentinel;
	RBTreeNode<K> * y = x;
	RBTreeNode<K> * z;
	bool y_original_color = y->color;
	if (x->left == nil) {
		z = x->right;
		transplant(x, x->right);
	}
	else if (x->right == nil) {
		z = x->left;
		transplant(x, x->left);
	}
	else {
		y = minimum(x->right, nil);
		z = y->right;
		y_original_color = y->color;
		if (y->parent == x) {
			z->parent = y;
		}
		else {
			transplant(y, y->right);
			y->right = x->right;
			x->right->parent = y;
		}
		y->left = x->left;
		x->left->parent = y;
		y->color = x->color;
		if (y_original_color == BLACK)
			rbDeleteFixup(z);
	}
}

template<typename K>
void RBTree<K>::transplant(RBTreeNode<K> * x, RBTreeNode<K> * y) {
	if (x == root) {
		root = y;
	}
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->parent = x->parent;
}

template<typename K>
void RBTree<K>::leftRotate(RBTreeNode<K> * x) {
	RBTreeNode<K> * y = x->right;
	transplant(x, y);
	x->right = y->left;
	x->right->parent = x;
}

template<typename K>
void RBTree<K>::rightRotate(RBTreeNode<K> * x) {
	RBTreeNode<K> * y = x->left;
	transplant(x, y);
	x->left = y->right;
	y->right->parent = x;
}

template<typename K>
void RBTree<K>::rbInsertFixup(RBTreeNode<K> * x) {
	RBTreeNode<K> * y;
	while (x != root && x->parent->color == RED) {
		if (x->parent == x->parent->parent->left) {
			y = x->parent->parent->right;
			if (y->color == RED) {
				y->color = BLACK;
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					leftRotate(x);
				}
				x->parent->parent->color = RED;
				x->parent->color = BLACK;
				rightRotate(x->parent->parent);
			}
		}
		else { //Symmetric to the "if" case
			y = x->parent->parent->left;
			if (y->color == RED) {
				y->color = BLACK;
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->left) {
					x = x->parent;
					rightRotate(x);
				}
				x->parent->parent->color = RED;
				x->parent->color = BLACK;
				leftRotate(x->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

template<typename K>
void RBTree<K>::rbDeleteFixup(RBTreeNode<K> * x) {
	RBTreeNode<K> * w;
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) { //1 -> 2,3,4
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == RED) { //3 -> 4
					w->color = RED;
					w->left->color = BLACK;
					w = w->left;
					rightRotate(w->parent);
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(w->parent);
				x = root;
			}
		}
		else {
			w = x->parent->left;
			if (w->color == RED) { //1 -> 2,3,4
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(x->parent);
				w = x->parent->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->right->color == RED) { // 3 -> 4
					w->color = RED;
					w->right->color = BLACK;
					w = w->right;
					leftRotate(w->parent);
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(w->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

#endif
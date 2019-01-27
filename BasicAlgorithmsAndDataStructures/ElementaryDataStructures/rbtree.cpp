#include <rbtree.h>

RBTree::RBTree()
{
	nil = new RBTreeNode();
	nil->left = nil->right = nil->parent = nil;
	root = nil;
	nil->color = BLACK;
}

RBTree::~RBTree()
{
	;
}

void RBTree::insert(RBTreeNode * x)
{
	if (root == nil) {
		root = x;
		x->parent = nil;
		x->color = BLACK;
		x->left = x->right = nil;
	}
	else {
		RBTreeNode *y = nil, *z = root;
		while (z != nil) {
			y = z;
			if (x->key < z->key)
				z = z->left;
			else
				z = z->right;
		}
		if (x->key < y->key)
			y->left = x;
		else
			y->right = x;
		x->parent = y;
		x->color = RED;
		x->left = x->right = nil;
		if (y->color == RED) insertFixup(x);
	}
}

void RBTree::remove(RBTreeNode * x)
{
	RBTreeNode * y = x, *z;
	int y_original_color = y->color;
	if (x->left == nil) {
		z = x->right;
		transplant(x, z);
	}
	else if (x->right == nil) {
		z = x->left;
		transplant(x, z);
	}
	else {
		y = minimum(x->right);
		z = y->right;
		y_original_color = y->color;
		if (y->parent != x) {
			transplant(y, z);
			y->right = x->right;
			y->right->parent = y;
		}
		transplant(x, y);
		y->left = x->left;
		y->left->parent = x->parent;
		y->color = x->color;
	}
	if (y_original_color == BLACK)
		removeFixup(z);
}

RBTreeNode * RBTree::search(const int & k)
{
	RBTreeNode * x = root;
	while (x != nil) {
		if (k < x->key)
			x = x->left;
		else if (k > x->key)
			x = x->right;
		else
			return x;
	}
	return nullptr;
}

RBTreeNode * RBTree::minimum(RBTreeNode * x)
{
	while (x->left != nil)
		x = x->left;
	return x;
}

RBTreeNode * RBTree::maximum(RBTreeNode * x)
{
	while (x->right != nil)
		x = x->right;
	return x;
}

void RBTree::transplant(RBTreeNode * x, RBTreeNode * y)
{
	if (x == root)
		root = y;
	if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->parent = x->parent;
}

RBTreeNode * RBTree::leftRotate(RBTreeNode * x)
{
	RBTreeNode * y = x->right;
	transplant(x, y);
	x->parent = y;
	y->left->parent = x;
	x->right = y->left;
	y->left = x;
	return y;
}

RBTreeNode * RBTree::rightRotate(RBTreeNode * x)
{
	RBTreeNode * y = x->left;
	transplant(x, y);
	x->parent = y;
	y->right->parent = x;
	x->left = y->right;
	y->right = x;
	return y;
}

void RBTree::insertFixup(RBTreeNode * x)
{
	while (x->parent->color == RED) {
		if (x->parent == x->parent->parent->left) {
			if (x->parent->parent->right->color == RED) {
				x->parent->color = BLACK;
				x->parent->parent->right->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					leftRotate(x);
				}
			}
			x->parent->color = BLACK;
			x->parent->parent->color = RED;
			rightRotate(x->parent->parent);
			x = x->parent;
		}
		else {
			if (x->parent->parent->left->color == RED) {
				x->parent->color = BLACK;
				x->parent->parent->left->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->left) {
					x = x->parent;
					rightRotate(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				leftRotate(x->parent->parent);
				x = x->parent;
			}
		}
	}
	root->color = BLACK;
}

void RBTree::removeFixup(RBTreeNode * x)
{
	while (x != root && x->color == BLACK) {
		RBTreeNode * w;
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) {
				x->parent->color = RED;
				w->color = BLACK;
				leftRotate(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == RED && w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = x->parent->right;
				}
				else {
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
		}
		else {
			if (x == x->parent->right) {
				w = x->parent->left;
				if (w->color == RED) {
					x->parent->color = RED;
					w->color = BLACK;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->right->color == RED && w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					else {
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						rightRotate(x->parent);
						x = root;
					}
				}
			}
		}
	}
	x->color = BLACK;
}

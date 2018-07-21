#include <bstree.h>

TreeNode * BinarySearchTree::maximum(TreeNode * x) {
	while (x->right != nil)
		x = x->right;
	return x;
}

TreeNode * BinarySearchTree::minimum(TreeNode * x) {
	while (x->left != nil)
		x = x->left;
	return x;
}

void BinarySearchTree::transplant(TreeNode * x, TreeNode *y) {
	if (x->parent == root)
		root = y;
	if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->parent = x->parent;
}

BinarySearchTree::BinarySearchTree() {
	nil = new TreeNode();
	nil->left = nil->right = nil->parent = nil;
	root = nil;
}

BinarySearchTree::~BinarySearchTree() {

}

void BinarySearchTree::insert(TreeNode * x) {
	if (root == nil) {
		root = x;
		x->parent = nil;
	}
	else {
		TreeNode *y = nil, *z = root;
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
	}
	x->left = x->right = nil;
}
void BinarySearchTree::remove(TreeNode * x) {
	if (x->left == nil)
		transplant(x, x->right);
	else if (x->right == nil)
		transplant(x, x->right);
	else {
		TreeNode * y = minimum(x->right);
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

TreeNode * BinarySearchTree::search(const int & k) {
	TreeNode * x = root;
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
#include <bstree.h>

void inorderVisit(const TreeNode * root, const TreeNode * sentinel, const int & n) {
	const TreeNode** stack = new const TreeNode*[n];
	const TreeNode * curr = root;
	int s = 0;
	while (curr != sentinel || s > 0) {
		while (curr != sentinel) {
			stack[s++] = curr;
			curr = curr->left;
		}
		curr = stack[--s];
		std::cout << curr->key << " ";
		curr = curr->right;
	}
	std::cout << std::endl;

	delete[] stack;
}

void depthGiveNode(const TreeNode * root, const TreeNode * sentinel, const int & n) {
	const TreeNode** stack = new const TreeNode*[n];
	int *stack_depth = new int[n];

	stack[0] = root;
	stack_depth[0] = 0;
	int s = 1;
	int init = 0, end = 1, curr_depth, max_depth = 0;
	const TreeNode * curr;
	while (s > 0) {
		curr_depth = stack_depth[init];
		max_depth = (curr_depth > max_depth) ? curr_depth : max_depth;
		curr = stack[init++];
		--s;
		if (curr->left != sentinel) {
			stack_depth[end] = curr_depth + 1;
			stack[end++] = curr->left;
			++s;
		}
		if (curr->right != sentinel) {
			stack_depth[end] = curr_depth + 1;
			stack[end++] = curr->right;
			++s;
		}
	}
	std::cout << "Depth : " << max_depth;
}

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
	size = 0;
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
	++size;
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
	--size;
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

int BinarySearchTree::getSize() const {
	return size;
}

const TreeNode * BinarySearchTree::getRoot() const {
	return root;
}

const TreeNode * BinarySearchTree::getSentinel() const {
	return nil;
}
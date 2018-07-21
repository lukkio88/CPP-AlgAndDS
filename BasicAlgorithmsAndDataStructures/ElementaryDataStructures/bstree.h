#ifndef __BS_TREE_H
#define __BS_TREE_H

struct TreeNode {
	int key;
	TreeNode *left, *right, *parent;
};

class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();

	void insert(TreeNode * x);
	void remove(TreeNode * x);
	TreeNode * search(const int & k);

protected:

	TreeNode * maximum(TreeNode * x);
	TreeNode * minimum(TreeNode * x);
	void transplant(TreeNode * x, TreeNode *y);

private:
	TreeNode * nil;
	TreeNode * root;
};

#endif
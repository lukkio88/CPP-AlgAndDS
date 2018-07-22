#ifndef __BS_TREE_H
#define __BS_TREE_H
#include <iostream>

struct TreeNode {
	int key;
	TreeNode *left, *right, *parent;
};

void inorderVisit(const TreeNode * root, const TreeNode * sentinel, const int & n);
void depthGiveNode(const TreeNode * root, const TreeNode * sentinel, const int & n);

class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();

	void insert(TreeNode * x);
	void remove(TreeNode * x);
	TreeNode * search(const int & k);
	int getSize() const;

	const TreeNode * getRoot() const;
	const TreeNode * getSentinel() const;
	

protected:

	TreeNode * maximum(TreeNode * x);
	TreeNode * minimum(TreeNode * x);
	void transplant(TreeNode * x, TreeNode *y);

private:
	TreeNode * nil;
	TreeNode * root;
	int size;
};

#endif
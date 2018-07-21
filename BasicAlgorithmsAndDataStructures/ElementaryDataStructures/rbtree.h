#ifndef __RB_TREE_H
#define __RB_TREE_H

constexpr int BLACK = 0;
constexpr int RED = 1;

struct RBTreeNode {
	int key;
	RBTreeNode * left, *right, *parent;
	int color;
};

class RBTree {
public:
	RBTree();
	~RBTree();

	void insert(RBTreeNode* x);
	void remove(RBTreeNode* x);
	RBTreeNode * search(const int & k);

protected:

	RBTreeNode * minimum(RBTreeNode * x);
	RBTreeNode * maximum(RBTreeNode * x);
	void transplant(RBTreeNode * x, RBTreeNode * y);
	RBTreeNode * leftRotate(RBTreeNode *x);
	RBTreeNode * rightRotate(RBTreeNode *x);

	void insertFixup(RBTreeNode * x);
	void removeFixup(RBTreeNode * x);

private:
	RBTreeNode * nil;
	RBTreeNode * root;
};

#endif
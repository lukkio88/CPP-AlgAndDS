#ifndef __RB_TREE_H
#define __RB_TREE_H

constexpr int BLACK = 0;
constexpr int RED = 1;

template<typename K>
struct RBTreeNode {
	int key;
	RBTreeNode<K> * left, *right, *parent;
	int color;
};

template<typename K>
class RBTree {
public:
	RBTree();
	~RBTree();

	void insert(RBTreeNode<K>* x);
	void remove(RBTreeNode<K>* x);
	RBTreeNode<K> * search(const int & k);

protected:

	RBTreeNode<K> * minimum(RBTreeNode<K> * x);
	RBTreeNode<K> * maximum(RBTreeNode<K> * x);
	void transplant(RBTreeNode<K> * x, RBTreeNode<K> * y);
	RBTreeNode<K> * leftRotate(RBTreeNode<K> *x);
	RBTreeNode<K> * rightRotate(RBTreeNode<K> *x);

	void insertFixup(RBTreeNode<K> * x);
	void removeFixup(RBTreeNode<K> * x);

private:
	RBTreeNode<K> * nil;
	RBTreeNode<K> * root;
};

#include "rbtree.tcc"

#endif
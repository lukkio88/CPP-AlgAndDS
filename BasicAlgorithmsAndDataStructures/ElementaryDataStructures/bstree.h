#ifndef __BS_TREE_H
#define __BS_TREE_H
#include <iostream>

template<typename K>
struct TreeNode {
	K key;
	TreeNode<K> *left, *right, *parent;
};

template<typename K>
void inorderVisit(const TreeNode<K> * root, const TreeNode<K> * sentinel, const int & n);

template<typename K>
void depthGiveNode(const TreeNode<K> * root, const TreeNode<K> * sentinel, const int & n);

template<typename K>
class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();

	void insert(TreeNode<K> * x);
	void remove(TreeNode<K> * x);
	TreeNode<K> * search(const K & k);
	int getSize() const;

	const TreeNode<K> * getRoot() const;
	const TreeNode<K> * getSentinel() const;
	

protected:

	TreeNode<K> * maximum(TreeNode<K> * x);
	TreeNode<K> * minimum(TreeNode<K> * x);
	void transplant(TreeNode<K> * x, TreeNode<K> *y);

private:
	TreeNode<K> * nil;
	TreeNode<K> * root;
	int size;
};

#include "bstree.tcc"

#endif
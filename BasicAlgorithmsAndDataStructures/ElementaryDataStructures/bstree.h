#ifndef __BS_TREE_H
#define __BS_TREE_H
#include <allocator.h>

template<typename K>
struct TreeNode {
	K key;
	TreeNode *left, *right, *parent;
};

template<typename K>
class BSTreeAllocator: public Allocator<TreeNode<K>> {
protected:
	void moveContentDefragment(Node<K>* source, Node<K>* destination) override
	{
		destination->key = source->key;

		//Setting pointers from y
		destination->left = source->prev;
		destination->next = source->next;
		destination->parent = source->parent;

		//Setting pointers pointing to x to y
		source->left->parent = destination;
		source->right->parent = destination;
		if (source == source->parent->left)
		{
			source->parent->left = destination;
		}
		else
		{
			source->parent->right = destination;
		}
	}
	void moveContentReallocate(Node<K>* source, Node<K>* destination, Node<K>* sourceMemory, Node<K>* destinationMemory) override 
	{
		destination->key = source->key;

		int parentOffset = source->parent - sourceMemory;
		int leftOffset = source->left - sourceMemory;
		int rightOffset = source->right - sourceMemory;

		destination->parent = destination->memory + parentOffset;
		destination->left = destination->memory + leftOffset;
		destination->right = destination->memory + rightOffset;
	}
};

template<typename K>
class BinarySearchTreeInterface {
public:
	BinarySearchTree(TreeNode<K> * nil);
	~BinarySearchTree();

	void insert(TreeNode * x);
	void remove(TreeNode * x);
	TreeNode * search(const int & k);

private:

	TreeNode * maximum(TreeNode * x);
	TreeNode * minimum(TreeNode * x);
	void transplant(TreeNode * x, TreeNode *y);

public:
	TreeNode * nil;
	TreeNode * root;
};

#endif
#ifndef __RB_TREE_TESTING_H
#define __RB_TREE_TESTING_H
#include<iostream>
#include <fstream>
#include <sstream>
#include<rbtree.h>

void print(const RBTree& l, const int stack_size);

class RBTreeTesting {
public:
	RBTreeTesting(std::string test_filename, const int stack_size);
	~RBTreeTesting();
	void runTest();
private:
	void perform_insert(int val);
	void perform_remove();
	void perform_search(int val);
private:
	int mStackSize;
	std::string filename;
	RBTree * mRBTreeTested;
	RBTreeNode * x;
	std::ifstream ifs;
};

#endif

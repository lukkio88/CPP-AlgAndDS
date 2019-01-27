#ifndef __BST_TESTING_H
#define __BST_TESTING_H
#include<iostream>
#include <fstream>
#include <sstream>
#include<bstree.h>

void print(const BinarySearchTree& l, const int stack_size);

class BinarySearchTreeTesting {
public:
	BinarySearchTreeTesting(std::string test_filename, const int stack_size);
	~BinarySearchTreeTesting();
	void runTest();
private:
	void perform_insert(int val);
	void perform_remove();
	void perform_search(int val);
private:
	int mStackSize;
	std::string filename;
	BinarySearchTree * mTreeTested;
	TreeNode * x;
	std::ifstream ifs;
};

#endif

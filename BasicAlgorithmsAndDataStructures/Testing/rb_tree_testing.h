#ifndef __RB_TREE_TESTING_H
#define __RB_TREE_TESTING_H
#include<unit_test.h>
#include<rbtree.h>

void print(const RBTree& l, const int stack_size);

class RBTreeTesting : public UnitTest {
public:
	RBTreeTesting(std::string test_filename, const int stack_size);
	~RBTreeTesting();
	void print_current_state();
private:
	void perform_insert(int val);
	void perform_remove();
	void perform_search(int val);
private:
	int mStackSize;
	RBTree * mRBTreeTested;
	RBTreeNode * x;
	std::ifstream ifs;
};

#endif

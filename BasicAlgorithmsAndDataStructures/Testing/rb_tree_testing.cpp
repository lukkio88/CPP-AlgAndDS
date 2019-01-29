#include <rb_tree_testing.h>

using std::ifstream;
using std::string;
using std::stringstream;
using std::getline;
using std::cout;
using std::endl;

void print(const RBTree& l, const int stack_size) {
	RBTreeNode ** stack = new RBTreeNode*[stack_size];
	int top = 0;
	RBTreeNode * x = l.root;
	if (x == l.nil)
		return;
	std::cout << "{ ";

	while (x != l.nil) {
		stack[top++] = x;
		x = x->left;
	}

	while (top > 0) {
		x = stack[--top];
		std::cout << x->key << " ";
		x = x->right;
		while (x != l.nil) {
			stack[top++] = x;
			x = x->left;
		}
	}
	std::cout << "}" << std::endl;
}

RBTreeTesting::RBTreeTesting(string test_filename, const int stack_size) :UnitTest(test_filename), mStackSize(stack_size), mRBTreeTested(new RBTree())
{

}

RBTreeTesting::~RBTreeTesting()
{
	delete mRBTreeTested;
}

void RBTreeTesting::print_current_state() {
	print(*mRBTreeTested, mStackSize);
}

void RBTreeTesting::perform_insert(int val)
{
	RBTreeNode * _x = new RBTreeNode();
	_x->key = val;
	mRBTreeTested->insert(_x);
}

void RBTreeTesting::perform_remove()
{
	mRBTreeTested->remove(x);
}

void RBTreeTesting::perform_search(int val)
{
	x = mRBTreeTested->search(val);
}

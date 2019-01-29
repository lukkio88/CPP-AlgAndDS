#include <bst_testing.h>

using std::ifstream;
using std::string;
using std::stringstream;
using std::getline;
using std::cout;
using std::endl;

void print(const BinarySearchTree& l, const int stack_size) {
	TreeNode ** stack = new TreeNode*[stack_size];
	int top = 0;
	TreeNode * x = l.root;
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

BinarySearchTreeTesting::BinarySearchTreeTesting(const string filename, const int stack_size): UnitTest(filename),mStackSize(stack_size),mTreeTested(new BinarySearchTree())
{

}

BinarySearchTreeTesting::~BinarySearchTreeTesting()
{
	delete mTreeTested;
}

void BinarySearchTreeTesting::print_current_state() {
	print(*mTreeTested, mStackSize);
}

void BinarySearchTreeTesting::perform_insert(int val)
{
	TreeNode * _x = new TreeNode();
	_x->key = val;
	mTreeTested->insert(_x);
}

void BinarySearchTreeTesting::perform_remove()
{
	mTreeTested->remove(x);
}

void BinarySearchTreeTesting::perform_search(int val)
{
	x = mTreeTested->search(val);
}

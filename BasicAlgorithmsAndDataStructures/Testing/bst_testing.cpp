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

BinarySearchTreeTesting::BinarySearchTreeTesting(string test_filename, const int stack_size) :mStackSize(stack_size), filename(test_filename), mTreeTested(new BinarySearchTree())
{

}

BinarySearchTreeTesting::~BinarySearchTreeTesting()
{
	delete mTreeTested;
}

void BinarySearchTreeTesting::runTest()
{
	string curr_line, command;
	stringstream ss;
	int val;
	ifstream ifs(filename);
	while (getline(ifs, curr_line)) {
		ss = stringstream(curr_line);
		ss >> command;

		if (command == "insert") {
			ss >> val;
			perform_insert(val);
			print(*mTreeTested, mStackSize);
		}
		else if (command == "remove") {
			perform_remove();
			print(*mTreeTested, mStackSize);
		}
		else if (command == "search") {
			ss >> val;
			perform_search(val);
			print(*mTreeTested, mStackSize);
		}
		else {
			cout << "Command not valid" << endl;
		}
	}
	cout << "Tree final state : " << endl;
	print(*mTreeTested, mStackSize);
	ifs.close();
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

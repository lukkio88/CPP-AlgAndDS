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

RBTreeTesting::RBTreeTesting(string test_filename, const int stack_size) :mStackSize(stack_size), filename(test_filename), mRBTreeTested(new RBTree())
{

}

RBTreeTesting::~RBTreeTesting()
{
	delete mRBTreeTested;
}

void RBTreeTesting::runTest()
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
			print(*mRBTreeTested,mStackSize);
		}
		else if (command == "remove") {
			perform_remove();
			print(*mRBTreeTested,mStackSize);
		}
		else if (command == "search") {
			ss >> val;
			perform_search(val);
			print(*mRBTreeTested,mStackSize);
		}
		else {
			cout << "Command not valid" << endl;
		}
	}
	cout << "RBTree final state : " << endl;
	print(*mRBTreeTested,mStackSize);
	ifs.close();
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

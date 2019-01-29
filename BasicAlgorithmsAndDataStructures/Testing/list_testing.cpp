#include <list_testing.h>

using std::ifstream;
using std::string;
using std::stringstream;
using std::getline;
using std::cout;
using std::endl;

void print(const List& l) {
	const Node * x = l.nil->next;
	if (x == l.nil)
		return;
	std::cout << "{";
	while (x != l.nil) {
		cout << x->key << " ";
		x = x->next;
	}
	cout << "}" << endl;

}

ListTesting::ListTesting(string test_filename):UnitTest(test_filename)
{
	mListTested = new List();
}

ListTesting::~ListTesting()
{
	delete mListTested;
}

void ListTesting::print_current_state() {
	print(*mListTested);
}

void ListTesting::perform_insert(int val)
{
	Node * _x = new Node();
	_x->key = val;
	mListTested->insert(_x);
}

void ListTesting::perform_remove()
{
	mListTested->remove(x);
}

void ListTesting::perform_search(int val)
{
	x = mListTested->search(val);
}

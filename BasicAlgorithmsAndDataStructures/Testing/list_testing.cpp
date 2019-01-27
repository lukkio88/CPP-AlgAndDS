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

ListTesting::ListTesting(string test_filename)
{
	filename = test_filename;
	mListTested = new List();
}

ListTesting::~ListTesting()
{
	delete mListTested;
}

void ListTesting::runTest()
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
			print(*mListTested);
		}
		else if (command == "remove") {
			perform_remove();
			print(*mListTested);
		}
		else if (command == "search") {
			ss >> val;
			perform_search(val);
			print(*mListTested);
		}
		else {
			cout << "Command not valid" << endl;
		}
	}
	cout << "List final state : " << endl;
	print(*mListTested);
	ifs.close();
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

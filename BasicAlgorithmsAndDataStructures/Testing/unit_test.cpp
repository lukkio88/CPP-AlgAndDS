#include <unit_test.h>

using std::ifstream;
using std::string;
using std::stringstream;
using std::getline;
using std::cout;
using std::endl;

UnitTest::UnitTest(string test_filename)
{
	filename = test_filename;
}

UnitTest::~UnitTest()
{
	;
}

void UnitTest::runTest()
{
	string curr_line, command;
	stringstream ss;
	int val;
	ifstream ifs(filename);
	while (getline(ifs, curr_line)) {
		ss = stringstream(curr_line);
		ss >> command;

		if (command == "insert") {
			while (ss >> val) {
				perform_insert(val);
			}
			print_current_state();
		}
		else if (command == "remove") {
			perform_remove();
			print_current_state();
		}
		else if (command == "search") {
			ss >> val;
			perform_search(val);
			print_current_state();
		}
		else {
			cout << "Command not valid" << endl;
		}
	}
	cout << "Final state : " << endl;
	print_current_state();
	ifs.close();
}

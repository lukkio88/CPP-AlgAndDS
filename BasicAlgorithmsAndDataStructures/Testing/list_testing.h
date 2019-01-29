#ifndef __LIST_TESTING_H
#define __LIST_TESTING_H
#include <unit_test.h>
#include<list.h>

void print(const List& l);

class ListTesting : public UnitTest {
public:
	ListTesting(std::string test_filename);
	~ListTesting();
	void print_current_state();
private:
	void perform_insert(int val);
	void perform_remove();
	void perform_search(int val);
private:
	List * mListTested;
	Node * x;
};

#endif
#ifndef __LIST_TESTING_H
#define __LIST_TESTING_H
#include<iostream>
#include <fstream>
#include <sstream>
#include<list.h>

void print(const List& l);

class ListTesting {
public:
	ListTesting(std::string test_filename);
	~ListTesting();
	void runTest();
private:
	void perform_insert(int val);
	void perform_remove();
	void perform_search(int val);
private:
	std::string filename;
	List * mListTested;
	Node * x;
	std::ifstream ifs;
};

#endif
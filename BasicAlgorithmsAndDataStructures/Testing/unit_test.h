#ifndef __UNIT_TEST_H
#define __UNIT_TEST_H
#include<iostream>
#include <fstream>
#include <sstream>

class UnitTest {
public:
	UnitTest(std::string test_filename);
	virtual ~UnitTest() = 0;
	virtual void runTest();
private:
	virtual void perform_insert(int val) = 0;
	virtual void perform_remove() = 0;
	virtual void perform_search(int val) = 0;
	virtual void print_current_state() = 0;
private:
	std::string filename;
};

#endif
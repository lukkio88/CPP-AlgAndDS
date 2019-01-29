#ifndef __SORTING_TEST_H
#define __SORTING_TEST_H

#include <iostream>
#include <fstream>

class SortingUnitTest {
public:
	SortingUnitTest(std::string filename);
	void run_test();
	virtual void sort() = 0;
private:
	std::string filename;
	int n_el;
	int * set;
};

#endif
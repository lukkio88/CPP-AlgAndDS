#include <list_testing.h>
#include <rb_tree_testing.h>
#include <bst_testing.h>
#include <Windows.h>

int main(int argc, char ** argv) {
	//system("dir");
	//ListTesting test("list_testing_program.txt");
	//BinarySearchTreeTesting test("list_testing_program.txt", 100);
	RBTreeTesting test("list_testing_program.txt", 100);
	test.runTest();
	return 0;
}
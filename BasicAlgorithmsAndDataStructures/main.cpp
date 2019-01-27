#include <list_testing.h>
#include <Windows.h>

int main(int argc, char ** argv) {
	//system("dir");
	ListTesting test("list_testing_program.txt");
	test.runTest();
	return 0;
}
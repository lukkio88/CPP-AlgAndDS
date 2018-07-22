#include <alg-and-ds.h>

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Error...\n");
	}
	else {
		test_binary_search_tree(argv[1]);
	}
	return 1;
}
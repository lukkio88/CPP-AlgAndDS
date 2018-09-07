#include <alg-and-ds.h>

int main(int argc, char **argv) {
	/*if (argc != 2) {
		printf("error...\n");
	}
	else {
		test_binary_search_tree(argv[1]);
	}*/

	List<int> l;

	Node<int> n[10];
	for (auto i = 0; i < 10; ++i) {
		n[i].val = 2 * i;
		l.insert(&n[i]);
	}

	Node<int>* first = l.search(0);



	return 0;
}
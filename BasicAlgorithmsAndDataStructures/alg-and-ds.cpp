#include <alg-and-ds.h>

int test_list(char *filename) {
	int n_test;
	List test_list;

	std::ifstream ifs(filename, std::ios::binary);
	std::stringstream ss;
	std::string line;

	std::getline(ifs,line);

	ss = std::stringstream(line);

	ss >> n_test;

	int curr_test = 0;
	while (curr_test < n_test) {
		int command, n_times, expected_size;
		std::getline(ifs, line);
		ss = std::stringstream(line);
		ss >> command >> n_times;
		int el;
		if (command == INSERT) {
			while (n_times > 0) {
				ss >> el;
				Node * node = new Node();
				node->key = el;
				test_list.insert(node);
				n_times--;
			}
			ss >> expected_size;
			if (expected_size != test_list.getSize()) {
				printf("List insert validation failed\n");
			}
		}
		else if (command == DELETE) {
			while (n_times > 0) {
				ss >> el;
				Node * node = test_list.search(el);
				if (node != nullptr)
					test_list.remove(node);
				n_times--;
			}
			ss >> expected_size;
			if (expected_size != test_list.getSize()) {
				printf("List delete validation failed\n");
			}
		}
		else if (command == SEARCH) {
			int found = 0;
			while (n_times > 0) {
				ss >> el;
				Node * node = test_list.search(el);
				found += (node != nullptr);
				--n_times;
			}
			ss >> expected_size;
			if (expected_size != found) {
				printf("List search validation failed\n");
			}
		}
		++curr_test;
	}
	printf("Validation successful!\n");
	ifs.close();
	return 0;
}

void test_binary_search_tree(char *filename) {

}

void test_red_black_tree(char *filename) {

}
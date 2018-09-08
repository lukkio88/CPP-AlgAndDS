#include <alg-and-ds.h>

using std::ifstream;
using std::stringstream;
using std::string;

int test_list(const string& filename) {
	ifstream ifs(filename);
	stringstream ss;
	string line;
	List<int> l;
	Node<int> *curr_node;

	int command;
	int n_el;
	int curr_el;

	while (std::getline(ifs, line)) {
		ss = stringstream(line);
		ss >> command;
		if (command == INSERT) {
			ss >> n_el;
			while (n_el > 0) {
				ss >> curr_el;
				curr_node = new Node<int>();
				curr_node->val = curr_el;
				l.insert(curr_node);
				n_el--;
			}
		}
		else if (command == SEARCH) {

		}
		else (command == DELETE) {

		}
	}
}

/*
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
*/

//int test_binary_search_tree(char *filename) {
//	int n_test;
//	BinarySearchTree test_tree;
//
//	std::ifstream ifs(filename, std::ios::binary);
//	std::stringstream ss;
//	std::string line;
//
//	std::getline(ifs, line);
//
//	ss = std::stringstream(line);
//
//	ss >> n_test;
//
//	int curr_test = 0;
//	while (curr_test < n_test) {
//		int command, n_times, expected_size;
//		std::getline(ifs, line);
//		ss = std::stringstream(line);
//		ss >> command >> n_times;
//		int el;
//		if (command == INSERT) {
//			while (n_times > 0) {
//				ss >> el;
//				TreeNode * node = new TreeNode();
//				node->key = el;
//				test_tree.insert(node);
//				n_times--;
//			}
//			ss >> expected_size;
//			if (expected_size != test_tree.getSize()) {
//				printf("Tree insert validation failed\n");
//			}
//			std::cout << "After insert : ";
//			inorderVisit(test_tree.getRoot(), test_tree.getSentinel(), test_tree.getSize());
//			depthGiveNode(test_tree.getRoot(), test_tree.getSentinel(), test_tree.getSize());
//		}
//		else if (command == DELETE) {
//			while (n_times > 0) {
//				ss >> el;
//				TreeNode * node = test_tree.search(el);
//				if (node != nullptr)
//					test_tree.remove(node);
//				n_times--;
//			}
//			ss >> expected_size;
//			if (expected_size != test_tree.getSize()) {
//				printf("Tree delete validation failed\n");
//			}
//			std::cout << "After delete : ";
//			inorderVisit(test_tree.getRoot(), test_tree.getSentinel(), test_tree.getSize());
//			depthGiveNode(test_tree.getRoot(), test_tree.getSentinel(), test_tree.getSize());
//		}
//		else if (command == SEARCH) {
//			int found = 0;
//			while (n_times > 0) {
//				ss >> el;
//				TreeNode * node = test_tree.search(el);
//				found += (node != nullptr);
//				--n_times;
//			}
//			ss >> expected_size;
//			if (expected_size != found) {
//				printf("Tree search validation failed\n");
//			}
//		}
//		++curr_test;
//	}
//	printf("Validation successful!\n");
//	ifs.close();
//	return 0;
//}
//
//int test_red_black_tree(char *filename) {
//	return 0;
//}
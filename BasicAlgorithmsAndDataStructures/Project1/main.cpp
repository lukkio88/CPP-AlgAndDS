#include "quicksort.h"

#include <vector>

using std::vector;

int main(int argc, char ** argv) {
	vector<int> v{ 7,8,6,5,4,3,2,1 };
	quicksort(v.data(),0,v.size()-1);
	for (auto i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
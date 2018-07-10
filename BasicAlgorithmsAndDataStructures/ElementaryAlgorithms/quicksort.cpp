#include "quicksort.h"

int partition(int * v, const int & a, const int & b) {
	int r = b;
	int j = a-1;
	int i = a;
	while (i < r) {
		if (v[i] < v[r]) {
			++j;
			swap(v[i], v[j]);
		}
		++i;
	}
	++j;
	swap(v[j], v[r]);
	return j;
}

void quicksort(int * v, const int & a, const int & b) {
	if (a < b) {
		int r = partition(v, a, b);
		quicksort(v, a, r - 1);
		quicksort(v, r + 1, b);
	}
}
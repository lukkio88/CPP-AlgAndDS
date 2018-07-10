#include "heapsort.h"

int left(const int & idx) {
	return 2 * idx + 1;
}

int right(const int & idx) {
	return 2 * idx + 2;
}

void heapFix(int * v, const int & size, const int & init_idx) {
	int left_idx, right_idx, max_idx;
	int n = init_idx;
	while (n < size) {
		left_idx = left(n);
		right_idx = right(n);
		if (right_idx < size) {
			if (v[left_idx] > v[right_idx]) {
				max_idx = left_idx;
			}
			else {
				max_idx = right_idx;
			}
		}
		else if (left_idx < size) {
			max_idx = left_idx;
		}
		else {
			return;
		}
		if (v[n] < v[max_idx]) {
			swap(v[n], v[max_idx]);
			n = max_idx;
		}
		else {
			return;
		}
	}
}

void heapify(int * v, const int & size) {
	int n = size - 1;
	while (n >= 0) {
		heapFix(v, size, n);
		n--;
	}
}

void heapSort(int * v, const int & size) {
	heapify(v, size);
	int curr_size = size;
	while(curr_size > 1) {
		swap(v[0], v[curr_size - 1]);
		--curr_size;
		heapFix(v, curr_size, 0);
	}
}
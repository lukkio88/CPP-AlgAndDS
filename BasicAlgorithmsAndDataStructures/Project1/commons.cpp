#include "commons.h"

void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int max(const int & a, const int & b) {
	if (a > b) return a;
	return b;
}

int min(const int & a, const int & b) {
	if (a > b) return b;
	return a;
}
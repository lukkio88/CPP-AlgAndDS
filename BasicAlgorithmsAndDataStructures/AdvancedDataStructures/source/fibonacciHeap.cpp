#include <fibonacciHeap.h>
#include <cmath>

FibonacciHeap::FibonacciHeap() {
	min = nullptr;
	n = 0;
}

FibNode * FibonacciHeap::getMin() const {
	return min;
}

void FibonacciHeap::insertNode(FibNode * x) {
	if (x == nullptr) return;

	if (min == nullptr) {
		min = x;
		x->next = x;
		x->prev = x;
	}
	else {
		x->next = min;
		x->prev = min->prev;
		min->prev->next = x;
		min->prev = x;
	}
	++n;

	if (x->key < min->key) {
		min = x;
	}

	x->parent = nullptr;

}

int FibonacciHeap::getN() const {
	return n;
}

void FibonacciHeap::merge(FibonacciHeap * h) {

	if (h->min == nullptr)
		return;
	else if (min == nullptr) {
		min = h->getMin();
		n = h->getN();
		return;
	}
	else {
		FibNode *u, *v, *w, *x;
		u = min;
		v = h->getMin();
		w = u->next;
		x = v->prev;

		u->next = v;
		v->prev = u;
		w->prev = x;
		x->next = w;
		n += h->getN();
		if (v->key < u->key)
			min = v;
	}
}

void FibonacciHeap::extractMin() {
	FibNode * x, *y, * z = min;
	if (z != nullptr) {
		x = z->child;
		x->prev->next = nullptr;
		while (x != nullptr) {
			y = x->next;
			insertNode(x);
			x = y;
		}
	}
	if (z == z->next) {
		min = nullptr;
	}
	else {
		min = z->next;
	}
	consolidate();
	--n;
}

void FibonacciHeap::consolidate() {
	int Dn = ilogb(n);
	FibNode ** A = new FibNode*[Dn];
	for (auto i = 0; i < Dn; ++i)
		A[i] = nullptr;

}
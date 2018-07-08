#include <fibonacciHeap.h>
#include <cmath>

FibNode * FibNode::insertNode(FibNode *y) {
	FibNode * x = this;
	if (x == nullptr && y != nullptr) {
		x = y;
		x->next = x;
		x->prev = x;
	}
	else if (x != nullptr && y != nullptr) {
		x->next->prev = y;
		y->next = x->next;
		y->prev = x;
		x->next = y;
	}
	return x;
}

FibNode * FibNode::remove() {
	FibNode * x = this;
	if (x->next == x)
		return nullptr;
	else {
		x->prev->next = x->next;
		x->next->prev = x->prev;
		return x->next;
	}
}

void FibNode::initParents() {
	FibNode * x, *y;
	x = this;
	do {
		x->parent = nullptr;
		x = x->next;
	} while (x != this);
}

FibNode * FibNode::joinList(FibNode *y) {
	FibNode * x = this;
	if (x == nullptr && y != nullptr)
		x = y;
	else if(x != nullptr && y != nullptr) {
		FibNode * u, *v;
		u = x->next;
		v = y->prev;
		x->next = y;
		y->prev = x;
		u->prev = v;
		v->next = u;
	}
	return x;
}

FibonacciHeap::FibonacciHeap() {
	min = nullptr;
	n = 0;
}

FibNode * FibonacciHeap::getMin() const {
	return min;
}

void FibonacciHeap::insertNode(FibNode * x) {
	if (x == nullptr) return;
	FibNode * tmp = min->insertNode(x);
	++n;
	if (tmp->key < min->key)
		min = tmp;
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
		FibNode * u = min;
		FibNode * v = h->getMin();
		u->joinList(v);
		n += h->getN();
		if (v->key < u->key)
			min = v;
	}
}

void FibonacciHeap::extractMin() {
	FibNode * x, *z = min;
	x = z->child;
	x->initParents();
	min = z->remove();
	min = min->joinList(x);
	if(n != 0)
		consolidate();
	--n;
}

void FibonacciHeap::consolidate() {
	int Dn = ilogb(n);
	FibNode ** A = new FibNode*[Dn];
	for (auto i = 0; i < Dn; ++i)
		A[i] = nullptr;
	FibNode * x, *y, *z, *tmp;
	x = min;
	while (x != nullptr) {
		y = x->remove();
		while (A[x->degree] != nullptr) {
			z = A[x->degree];
			A[x->degree] = nullptr;
			if (z->key < x->key) {
				tmp = x;
				x = z;
				z = tmp;
			}
			z->parent = x;
			x->child->insertNode(z);
			x->degree += 1;
		}
		x = y;
	}
	for (auto i = 0; i < Dn; ++i) {
		if (A[i] != nullptr) {
			if (min != nullptr)
				min->insertNode(A[i]);
			else
				min = A[i];
			
			if (min->key > A[i]->key)
				min = A[i];
		}
	}
}
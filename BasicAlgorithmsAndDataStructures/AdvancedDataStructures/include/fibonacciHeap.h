#pragma once

struct FibNode {
	int key;
	bool marked;
	int degree;
	FibNode * next, *prev, *parent, *child;
};

class FibonacciHeap {
public:
	FibonacciHeap();
	FibNode * getMin() const;
	void insertNode(FibNode * x);
	int getN() const;
	void merge(FibonacciHeap * h);
	void extractMin();
private:
	void consolidate();
	FibNode * min;
	int n;
};
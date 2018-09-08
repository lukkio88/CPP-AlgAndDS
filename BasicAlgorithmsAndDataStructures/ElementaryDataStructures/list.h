#ifndef __LIST_H
#define __LIST_H

template<typename V>
struct Node {
	V val;
	Node<V> *prev, *next;
};

template<typename V>
class List {
public:
	List();
	~List();
	void insert(Node<V> * x);
	void remove(Node<V> * x);
	Node<V> * search(const V & k);
	int getSize() const;
private:
	Node<V> *nil;
	int size;
};

template<typename V>
class ListValidator {
public:
	ListValidator(List<V>* x);
	friend bool noLoopForward();
	friend bool noLoopBackward();
private:
	List<V> *l;
};

#include "list.tcc"

#endif
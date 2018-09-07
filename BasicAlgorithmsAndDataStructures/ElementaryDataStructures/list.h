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

#include "list.tcc"

#endif
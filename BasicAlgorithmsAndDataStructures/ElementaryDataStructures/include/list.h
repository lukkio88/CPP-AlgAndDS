#pragma once
#ifndef __LIST_H
#define __LIST_H
#include <iostream>

template<typename K>
struct Node {
	K key;
	Node *next;
	Node *prev;
};

template<typename K>
class List {
public:
	List();
	void insertFirst(Node<K> * x);
	void insertLast(Node<K> * x);
	Node<K> * getFirst();
	Node<K> * getLast();
	void removeNode(Node<K> * x);
	Node<K> * find(const K & key);
private:
	Node<K> * first;
	Node<K> * last;
};

template<typename K>
List<K>::List() {
	first = last = nullptr;
}

template<typename K>
void List<K>::insertFirst(Node<K> * x) {
	if (first == nullptr) {
		first = x;
		last = x;
		x->prev = nullptr;
		x->next = nullptr;
	}
	else {
		x->next = first;
		x->prev = nullptr;
		first->prev = x;
		first = x;
	}
}

template<typename K>
void List<K>::insertLast(Node<K> * x) {
	if (last == nullptr) {
		first = x;
		last = x;
		x->prev = nullptr;
		x->next = nullptr;
	}
	else {
		x->next = nullptr;
		x->prev = last;
		last->next = x;
		last = x;
	}
}

template<typename K>
Node<K> * List<K>::getFirst() {
	return first;
}

template<typename K>
Node<K> * List<K>::getLast() {
	return last;
}

template<typename K>
void List<K>::removeNode(Node<K> * x) {
	if (first == last) {
		first = last = nullptr;
	}
	else if (x == first) {
		first = first->next;
		first->prev = nullptr;
	}
	else if (x == last) {
		last = last->prev;
		last->next = nullptr;
	}
	else {
		x->prev->next = x->next;
		x->next->prev = x->prev;
	}
}

template<typename K>
Node<K> * List<K>::find(const K & key) {
	Node<K> * x = first;
	while (x != nullptr) {
		if (x->key == key) {
			break;
		}
		x = x->next;
	}
	return x;
}

//tests
void test_list();

#endif
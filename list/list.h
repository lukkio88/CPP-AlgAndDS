/*
 * list.h
 *
 *  Created on: 18 Mar 2017
 *      Author: Lukkio
 */

#ifndef LIST_LIST_H_
#define LIST_LIST_H_

#include "list_node.h"
#include <iostream>

template<typename K>
class List {
public:

	class Iterator;

	List();
	List(const List<K>& x);
	~List();
	void insert(const K& x);
	List<K>::Iterator begin();
	List<K>::Iterator end();
	List<K>::Iterator search(K k);
	void remove(List<K>::Iterator it);
	Node<K>* getSentinel() const;

	class Iterator {
	public:
		Iterator();
		Iterator(const List<K>& x);
		~Iterator();
		Iterator(const Iterator& it);                   // Copy constructor
		List<K>::Iterator& operator=(const Iterator& it); // Assignment operator
		List<K>::Iterator& operator++();                   // Next element
		K& operator*();                    // Dereference
		bool operator==(const Iterator& o) const; // Comparison
		bool operator!=(const Iterator& o) const;
		void setCurrent(Node<K> * const & x);
		Node<K>* getCurr() const;
	private:
		Node<K> * curr;
	};

private:
	Node<K> *sentinel;
};

template<typename K>
inline List<K>::List() {
	this->sentinel = new Node<K>();
}

template<typename K>
inline List<K>::List(const List<K>& x) {
	Node<K>* curr = x.getSentinel()->getNext();
	while (curr != x.getSentinel()) {
		this->insert(curr->getKey());
		curr = curr->getNext();
	}
}

template<typename K>
inline List<K>::~List() {
	Node<K> *curr, *nil;
	nil = this->getSentinel();
	curr = nil->getNext();
	while(curr != nil) {
		curr->removeNode(nil);
		delete curr;
		curr = nil->getNext();
	}
}

template<typename K>
inline void List<K>::insert(const K& x) {
	Node<K>* node = new Node<K>();
	Node<K>* nil = this->getSentinel();
	node->setKey(x);
	node->insertNode(nil);
}

template<typename K>
Node<K>* List<K>::getSentinel() const {
	return this->sentinel;
}

template<typename K>
inline typename List<K>::Iterator List<K>::begin() {
	List<K>::Iterator it(*this);
	++it;
	return it;
}

template<typename K>
inline typename List<K>::Iterator List<K>::end() {
	return List<K>::Iterator(*this);
}

template<typename K>
inline typename List<K>::Iterator List<K>::search(K k) {
	List<K>::Iterator it(*this);
	for (it = this->begin(); it != this->end(); ++it) {
		if (*it == k)
			return it;
	}
	return it;
}

template<typename K>
inline void List<K>::remove(List<K>::Iterator it) {
	Node<K>* curr = it.getCurr();
	curr->removeNode(this->getSentinel());
	delete curr;
}

template<typename K>
inline List<K>::Iterator::Iterator() {
	this->setCurrent(0);
}

template<typename K>
inline List<K>::Iterator::Iterator(const List<K>& x) {
	this->setCurrent(x.getSentinel());
}

template<typename K>
inline List<K>::Iterator::~Iterator() {
	;
}

template<typename K>
inline List<K>::Iterator::Iterator(const Iterator& it) {
	this->setCurrent(it.getCurr());
}

template<typename K>
inline typename List<K>::Iterator& List<K>::Iterator::operator =(
		const Iterator& it) {
	if (this != &it) {
		this->setCurrent(it.getCurr());
	}
	return *this;
}

template<typename K>
inline typename List<K>::Iterator& List<K>::Iterator::operator ++() {
	this->setCurrent(this->getCurr()->getNext());
	return *this;
}

template<typename K>
inline K& List<K>::Iterator::operator *() {
	return this->getCurr()->getKeyRef();
}

template<typename K>
inline bool List<K>::Iterator::operator ==(const Iterator& o) const {
	return this->getCurr() == o.getCurr();
}

template<typename K>
inline bool List<K>::Iterator::operator!=(const Iterator& o) const {
	return !(*this == o);
}

template<typename K>
inline void List<K>::Iterator::setCurrent(Node<K>* const & x) {
	this->curr = x;
}

template<typename K>
inline Node<K>* List<K>::Iterator::getCurr() const {
	return this->curr;
}

#endif /* LIST_LIST_H_ */

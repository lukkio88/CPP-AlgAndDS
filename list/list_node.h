/*
 * list.h
 *
 *  Created on: 25 Feb 2017
 *      Author: Lukkio
 */

#ifndef LIST_H_
#define LIST_H_

template<typename K>
class Node {
public:
	Node();
	Node(const Node<K>& x);
	void setKey(const K& x);
	void setNext(Node<K> * const & x);
	void setPrev(Node<K> * const & x);
	Node<K>* getNext() const;
	Node<K>* getPrev() const;
	void insertNode(Node<K>* const & nil);
	void removeNode(Node<K>* const & nil);
	K getKey() const;
	K& getKeyRef();
private:
	K key;
	Node<K>* next;
	Node<K>* prev;
};

template<typename K>
inline Node<K>::Node() {
	this->setNext(this);
	this->setPrev(this);
}

template<typename K>
inline Node<K>::Node(const Node<K>& x) {
	this->setKey(x.getKey());
	this->setPrev(x.getPrev());
	this->setNext(x.getNext());
}

template<typename K>
inline void Node<K>::setKey(const K& x) {
	this->key = x;
}

template<typename K>
inline void Node<K>::setNext(Node<K> * const & x) {
	this->next = x;
}

template<typename K>
inline void Node<K>::setPrev(Node<K> * const & x) {
	this->prev = x;
}

template<typename K>
inline Node<K>* Node<K>::getNext() const {
	return this->next;
}

template<typename K>
inline Node<K>* Node<K>::getPrev() const {
	return this->prev;
}

template<typename K>
inline K Node<K>::getKey() const {
	return this->key;
}

template<typename K>
inline K& Node<K>::getKeyRef() {
	return this->key;
}

template<typename K>
inline void Node<K>::insertNode(Node<K>* const & nil) {
	this->setPrev(nil->getPrev());
	this->setNext(nil);
	nil->getPrev()->setNext(this);
	nil->setPrev(this);
}

template<typename K>
inline void Node<K>::removeNode(Node<K>* const & nil) {
	Node<K> *prev, *next;
	if(this != nil) {
		prev = this->getPrev();
		next = this->getNext();
		prev->setNext(next);
		next->setPrev(prev);
	}
}

#endif /* LIST_H_ */

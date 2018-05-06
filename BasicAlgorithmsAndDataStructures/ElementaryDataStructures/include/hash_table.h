#pragma once
#ifndef __HASH_TABLE_H
#define __HASH_TABLE_H

#include <array>

template<typename _K, typename _V>
class HashTableNode {
	_K key;
	_V val;
	HashTableNode * next, *prev;
};

//Implementing hash table with collision
template<typename _K,typename _V, int _Size>
class HashTable {
public:
	HashTable(int (*hashFunc)(_K));
	~HashTable();
	void insert(HashTableNode<_K,_V> * x);
	HashTableNode<_K, _V> * search(_K k);
	void remove(HashTableNode<_K, _V> * x);
private:
	int(*h)(_K); //hash function
	std::array<HashTableNode<_K,_V>*, _Size> collisionTable;
};

template<typename _K, typename _V, int _Size>
HashTable<_K, _V, _Size>::HashTable(int(*hashFunc)(_K)) {
	h = hashFunc;
	for (auto i = 0; i < _N; ++i)
		collisionTable[i] = nullptr;
}

template<typename _K, typename _V, int _Size>
HashTable<_K, _V, _Size>::~HashTable() {
	;
}

template<typename _K, typename _V, int _Size>
void HashTable<_K, _V, _Size>::insert(HashTableNode<_K, _V> * x) {
	int idx = h(x->key);
	x->prev = nullptr;
	x->next = collisionTable[i];
	collisionTable[i] = node;
}

template<typename _K, typename _V, int _Size>
HashTableNode<_K, _V> * HashTable<_K, _V, _Size>::search(_K k) {
	int idx = h(k);
	HashTableNode<_K, _V> * x = collisionTable[i];
	while (x != nullptr && x->key != k) {
		x = x->next;
	}
	return x;
}

template<typename _K, typename _V, int _Size>
void HashTable<_K, _V, _Size>::remove(HashTableNode<_K, _V> * x) {
	int idx = h(x->key);
	if (x->prev == collisionTable[i]) {
		collisionTable[i] = x->next;
	}

	if (x->prev != nullptr)
		x->prev->next = x->next;
	if (x->next != nullptr)
		x->next->prev = x->next;
}

#endif
#ifndef __LIST_H
#define __LIST_H
#include <allocator.h>

template<typename Data>
struct Node {
	Data key;
	Node *prev, *next;
};

template<typename Data>
class ListAllocator : public Allocator<Node<Data>>
{
public:
	ListAllocator(int maxSize) :Allocator<Node<Data>>(maxSize) { ; }
protected:
	void moveContentDefragment(Node<Data>* source, Node<Data>* destination) override
	{
		destination->key = source->key;
		
		//setting pointers from the destination
		destination->prev = source->prev;
		destination->next = source->next;
		
		//setting pointers to the destination
		destination->prev->next = destination;
		destination->next->prev = destination;
	}
	void moveContentReallocate(Node<Data>* source, Node<Data>* destination, Node<Data>* memorySource, Node<Data>* memoryDestination) override 
	{
		destination->key = source->key;

		int prevOffset = source->prev - memorySource;
		int nextOffset = source->next - memorySource;
		destination->prev = memoryDestination + prevOffset;
		destination->next = memoryDestination + nextOffset;
	}
};

/**
 * @brief List interface, see CLRS.
 * @tparam T 
*/
template<typename T>
class ListInterface {
public:
	ListInterface(Node<T>* sentinel)
	{
		nil = sentinel;
		nil->next = nil;
		nil->prev = nil;
	}
	void insertFront(Node<T>* x)
	{
		x->prev = nil;
		x->next = nil->next;
		nil->next->prev = x;
		nil->next = x;
	}
	void insertBack(Node<T>* x)
	{
		x->prev = nil->prev;
		x->next = nil;
		nil->prev->next = x;
		nil->prev = x;
	}
	void remove(Node<T>* x)
	{
		x->next->prev = x->prev;
		x->prev->next = x->next;
	}
	Node<T>* search(const T& key)
	{
		Node<T>* current = nil->next;
		while (current != nil)
		{
			if (current->key == key)
				return current;
			current = current->next;
		}
	}
public:
	Node<T> *nil;
};

/**
 * @brief Implements a list with a stack allocator
 * @tparam T 
*/
template<typename T>
class List {
public:
	List():allocator(10), interface(allocator.allocate())
	{
	}
	void append(const T& key)
	{
		Node<T>* node = allocator.allocate();
		node->key = key;
		interface.insertFront(node);
	}
	void preprend(const T& key)
	{
		Node<T>* node = allocate();
		node->key = key;
		interface.insertBack(node);
	}
	void popFront()
	{
		if (nil->next != nil) 
		{
			interface.remove(nil->next);
			allocator.deallocate(nil->next);
		}
	}
	void popBack()
	{
		if (nil->prev != nil)
		{
			interface.remove(nil->prev);
			allocator.deallocate(nil->prev);
		}
	}

	struct Iterator
	{
		Iterator operator++()
		{
			Node<T>* current = mCurrent;
			mCurrent = mCurrent->next;
			return Iterator{ current };
		}
		Iterator& operator++(int)
		{
			mCurrent = mCurrent->next;
			return *this;
		}
		bool operator==(const Iterator& it) const
		{
			return mCurrent == it.mCurrent;
		}

		bool operator!=(const Iterator& it) const
		{
			return !(*this == it);
		}

		T& operator*() {
			return mCurrent->key;
		}

		Node<T>* mCurrent;
	};

	Iterator begin() {
		return Iterator{ interface.nil->next };
	}

	Iterator end() {
		return Iterator{ interface.nil };
	}

private:
	ListAllocator<T> allocator;
	ListInterface<T> interface;
};

#endif
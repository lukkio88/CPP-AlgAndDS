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
	/**
	 * @brief Create interface with default sentinel
	 * @param sentinel initial node to be used as sentinel
	 * @return 
	*/
	ListInterface(Node<T>* sentinel)
	{
		nil = sentinel;
		nil->next = nil;
		nil->prev = nil;
	}

	/**
	 * @brief Insert new node at the front
	 * @param x Node to be inserted
	*/
	void insertFront(Node<T>* x)
	{
		x->prev = nil;
		x->next = nil->next;
		nil->next->prev = x;
		nil->next = x;
	}

	/**
	 * @brief Insert new node at the back
	 * @param x Node to be inserted
	*/
	void insertBack(Node<T>* x)
	{
		x->prev = nil->prev;
		x->next = nil;
		nil->prev->next = x;
		nil->prev = x;
	}

	/**
	 * @brief Remove node
	 * @param x Node to be removed
	*/
	void remove(Node<T>* x)
	{
		x->next->prev = x->prev;
		x->prev->next = x->next;
	}

	/**
	 * @brief Search for node with given key
	 * @param key 
	 * @return 
	*/
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

	/**
	 * @brief Re-set the sentinel node
	 * @param sentinel 
	*/
	void setNil(Node<T>* sentinel)
	{
		nil = sentinel;
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
	/**
	 * @brief Create empty list
	 * @tparam T 
	*/
	List():allocator(10), interface(allocator.allocate())
	{
	}

	/**
	 * @brief Append key
	 * @tparam T key
	*/
	void append(const T& key)
	{
		Node<T>* node = allocator.allocate();
		node->key = key;
		interface.setNil(allocator.getBaseOffset());
		interface.insertFront(node);
	}

	/**
	 * @brief Prepend key
	 * @param key 
	*/
	void preprend(const T& key)
	{
		Node<T>* node = allocate();
		node->key = key;
		interface.setNil(allocator.getBaseOffset());
		interface.insertBack(node);
	}

	/**
	 * @brief Remove front node
	*/
	void popFront()
	{
		if (nil->next != nil) 
		{
			interface.remove(nil->next);
			allocator.deallocate(nil->next);
			interface.setNil(allocator.getBaseOffset());
		}
	}

	/**
	 * @brief Remove back node
	*/
	void popBack()
	{
		if (nil->prev != nil)
		{
			interface.remove(nil->prev);
			allocator.deallocate(nil->prev);
			interface.setNil(allocator.getBaseOffset());
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
#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

/**
 * @brief Stack allocator
 * @tparam T Type of the nodes to be allocated
*/
template<typename T>
class Allocator
{
public:
	/**
	 * @brief Constructor
	 * @param maxSize Initial maximum size
	 * @return 
	*/
	Allocator(int maxSize) {
		mMaxSize = maxSize;
		mMemory = new T[mMaxSize];
		mFlag = new bool[mMaxSize];
		currentSize = 0;
		top = 0;
	}

	~Allocator()
	{
		delete[] mMemory;
		delete[] mFlag;
	}

	/**
	 * @brief Mark a node as allocated and return the pointer
	 * @return pointer to the requested node
	*/
	T* allocate()
	{
		T* block = &mMemory[top];
		mFlag[top++] = true;
		++currentSize;
		if (currentSize == mMaxSize/2)
		{
			//Notice that "top" in this case will have value mMaxSize / 2
			defragment();
			reallocate(2 * mMaxSize);
		}

		//Notice that if 
		if (top == (5*currentSize)/3) //Observe that since currentSize < mMaxSize/2 we have top < mMaxSize
		{
			defragment();
		}
		return block;
	}

	/**
	 * @brief Mark a node as de-allocated
	 * @param ptr Pointer of the node to be de-allocated
	*/
	void deallocate(T* ptr)
	{
		mFlag[ptr - mMemory] = false;
		currentSize--;
		if (currentSize == mMaxSize / 4)
		{
			defragment();
			reallocate(mMaxSize / 2);
		}
		if (top == (5*currentSize)/2)
		{
			defragment();
		}
	}

	/**
	 * @brief Defragment memory pool
	*/
	void defragment()
	{
		int indexDeallocatedNode = 0;
		int indexAllocatedNode = top;
		bool defragmenting = true;
		while (defragmenting)
		{
			while (mFlag[indexDeallocatedNode])
				++indexDeallocatedNode;
			while (!mFlag[indexAllocatedNode])
				--indexAllocatedNode;

			if (indexDeallocatedNode < indexAllocatedNode)
			{
				moveContentDefragment(&mMemory[indexAllocatedNode], &mMemory[indexDeallocatedNode]); //move the rightmost updated into the leftmost deallocated
				mFlag[indexDeallocatedNode] = true; //mark the deallocated as allocated
				mFlag[indexAllocatedNode] = false; //mark the previous allocated as deallocated
				--top;
			}
			else {
				defragmenting = false;
			}
		}
	}
	void reallocate(int size)
	{
		T* reallocatedMemory = new T[size];
		bool* reallocatedFlag = new bool[size];
		int reallocatedTop;
		int reallocatedCurrentSize = 0;
		for (int i = 0; i < size && i < top; ++i)
		{
			if (mFlag[i])
			{
				reallocatedFlag[i] = true;
				moveContentReallocate(&mMemory[i], &reallocatedMemory[i],mMemory, reallocatedMemory);
				reallocatedTop = i + 1;
				++reallocatedCurrentSize;
			}
		}
		
		delete[] mMemory;
		delete[] mFlag;

		mMemory = reallocatedMemory;
		mFlag = reallocatedFlag;
		mMaxSize = size;
		top = reallocatedTop;
		currentSize = reallocatedCurrentSize;
	}
protected:
	/**
	 * @brief Copy function for defragment
	 * @param source 
	 * @param destinatin 
	*/
	virtual void moveContentDefragment(T* source, T* destination) = 0;

	/**
	 * @brief Copy function for reallocate
	 * @param source 
	 * @param destination 
	 * @param memorySource 
	 * @param memoryDestination 
	*/
	virtual void moveContentReallocate(T* source, T* destination, T* memorySource, T* memoryDestination) = 0;
private:
	T* mMemory; //!< memory pool
	bool* mFlag; //!< flags marking allocated nodes
	int mMaxSize; //!< max size of this allocator
	int currentSize; //!< current number of nodes held by this allocator
	int top; //!< Pointer to the rightmost element allocated
};

#endif